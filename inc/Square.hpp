#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "GameObject.hpp"

class Square : public GameObject {
public:
    Square(cv::Scalar color, Size size, Speed speed, Position pos)
        : GameObject(color, size, speed, pos) {}

    void move() override;
    void draw(cv::Mat& frame) override;
    bool checkCollision(const cv::Rect& face) override;
};

#endif // SQUARE_HPP
