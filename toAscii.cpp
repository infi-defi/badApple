#include <opencv4/opencv2/opencv.hpp>
#include "toAscii.h"
#include <iostream>
#include <cmath>

void AsciiArtConverter::setImage(const cv::Mat& frame) {
  image = frame.clone();
}

void AsciiArtConverter::generateAsciiArt() {
  if (image.empty()) {
    std::cerr << "Error: No image data to convert.\n";
    return;
  }

  // resize settings
  const int maxWidth = 100;
  float aspectRatio = static_cast<float>(image.rows) / image.cols;
  int newWidth = std::min(maxWidth, image.cols);
  int newHeight = static_cast<int>(aspectRatio * newWidth * 0.5);  // adjust for height bc characters too tall ;-;

  // actual resize
  cv::Mat resized;
  cv::resize(image, resized, cv::Size(newWidth, newHeight));

  asciiArt.clear(); // clear in case it has stored stuff

  for (int y = 0; y < resized.rows; ++y) {
    std::string line;
    for (int x = 0; x < resized.cols; ++x) {
      cv::Vec3b color = resized.at<cv::Vec3b>(y, x);
      double r = color[2]; // opencv uses bgr for some reason.
      double g = color[1];
      double b = color[0];

      // light formula thing (thx google)
      int gray = std::ceil(0.21 * r + 0.72 * g + 0.07 * b);
      //              ^btw ceil returns the smallest integer that is greater than or equal to the input value.

      // quirky innit? 
      int idx = (gray * (lightmap.length() - 1)) / 255;
      line += lightmap[idx];
    }
    asciiArt.push_back(line);
  }
}

// print tihi~
void AsciiArtConverter::printAsciiArt() const {
  for (const std::string& line : asciiArt) {
    std::cout << line << std::endl;
  }
}
