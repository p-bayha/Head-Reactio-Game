#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>

struct Size {
    int width;
    int height;
};

struct Speed {
    float y;  // only vertical speed for simplicity
};

using Position = cv::Point;
using Color = cv::Scalar;

#endif // UTILS_HPP
