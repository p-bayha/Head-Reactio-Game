#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "GameObject.hpp"

class Square : public GameObject {
public:
    // Constructs a square with color, size, speed, and position
    Square(cv::Scalar color, Size size, Speed speed, Position pos)
        : GameObject(color, size, speed, pos) {}

    // Moves the square down by its speed
    void move() override;
    // Draws the square on the frame
    void draw(cv::Mat& frame) override;
    // Checks if the square collides with a given rectangle (face)
    bool checkCollision(const cv::Rect& face) override;
};

#endif // SQUARE_HPP
