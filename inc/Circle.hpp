#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "GameObject.hpp"

// Represents a falling ball in the DodgeBalls game mode
class Circle : public GameObject {
public:
    // Constructs a circle with color, size, speed, and position
    Circle(cv::Scalar color, Size size, Speed speed, Position pos)
        : GameObject(color, size, speed, pos) {}

    // Moves the circle down by its speed
    void move() override;
    // Draws the circle on the frame
    void draw(cv::Mat& frame) override;
    // Checks if the circle collides with a given rectangle (face)
    bool checkCollision(const cv::Rect& face) override;
    // Checks if the circle's bounding box intersects with a rectangle
    bool intersects(const cv::Rect& face);
};

#endif // CIRCLE_HPP
