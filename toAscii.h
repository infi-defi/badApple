#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <vector>

class AsciiArtConverter {
private:
  cv::Mat image;                        // current image frame
  std::vector<std::string> asciiArt;   // ascii representation
  const std::string lightmap = " .:=+*#%@"; // Brightness to character scale


public:
  AsciiArtConverter() = default;

  // Set an image directly (for video frames)
  void setImage(const cv::Mat& frame);

  // turn frame into ascii
  void generateAsciiArt();

  // hint: what it does is in the name :O
  void printAsciiArt() const;
};