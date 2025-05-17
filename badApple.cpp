#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include "toAscii.h"
#include <chrono>
#include <cstdlib>  // to find ~
#include <string>
#include <thread>

void clearScreen() {
    // this clears the screen for reasons still uknown to me
    std::cout << "\033[2J\033[1;1H";
}

std::string expandTilde(const std::string& path) { // find the home path
    if (!path.empty() && path[0] == '~') {
        const char* home = getenv("HOME");
        if (home) {
            return std::string(home) + path.substr(1);
        } else {
            // fallback if HOME not set
            return path;
        }
    }
    return path;
}

int main() {
    AsciiArtConverter converter;

    // help me out I cant seem to get this window open~
    std::string videoPath = "~/Videos/.badApple/bad_apple.mp4";
    videoPath = expandTilde(videoPath);
    cv::VideoCapture video(videoPath);
    // nevermind now its open~
    if (!video.isOpened()) {
        std::cerr << "Error: Could not open video." << std::endl;
        return 1;
    }

    double fps = video.get(cv::CAP_PROP_FPS);
    if (fps <= 0) fps = 30; // like, 0 fps aint that poggers so let us make it 30
    int delay = static_cast<int>(1000.0 / fps); // delay in milliseconds

    cv::Mat frame;

    while (true) {
        if (!video.read(frame) || frame.empty()) {
            break; // if this happens its probs the end of the video. If not panic
        }

        converter.setImage(frame);
        converter.generateAsciiArt();
        clearScreen();
        converter.printAsciiArt(); 
        // ^should've probs been a func in main.cpp but I came to that realization a bit late :|

        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); 
        // ^this is the delay but for all i know it could be mining bitcoin
    }

    std::cout << "Video playback done!" << std::endl; // yippie!
    return 0;
}
