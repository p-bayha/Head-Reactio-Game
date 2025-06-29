#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "GameObject.hpp"

class Circle : public GameObject {
public:
    Circle(cv::Scalar color, Size size, Speed speed, Position pos)
        : GameObject(color, size, speed, pos) {}

    void draw(cv::Mat& frame) override;
    bool checkCollision(const cv::Rect& face) override;
};

#endif // CIRCLE_HPP
