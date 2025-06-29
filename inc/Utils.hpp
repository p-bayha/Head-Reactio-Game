#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>

struct Size {
    int width;
    int height;
};

struct Speed {
    float y;  // nur vertikal
};

using Position = cv::Point;
using Color = cv::Scalar;

#endif // UTILS_HPP
