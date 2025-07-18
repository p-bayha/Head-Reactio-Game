#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <opencv2/opencv.hpp>
#include "Utils.hpp"

class GameObject {
public:
    // Constructs a game object with color, size, speed, and position
    GameObject(cv::Scalar color, Size size, Speed speed, Position pos)
        : m_color(color), m_size(size), m_speed(speed), m_position(pos) {}

    // Virtual destructor: ensures proper cleanup of derived objects
    virtual ~GameObject() = default;

    // Move the object by its speed (default: do nothing, override in derived)
    virtual void move() = 0;

    // Draws the object on the frame
    virtual void draw(cv::Mat& frame) = 0;
    // Checks if the object collides with a given rectangle (face)
    virtual bool checkCollision(const cv::Rect& face) = 0;

    // Getters for position and size
    Position getPosition() const { return m_position; } 
    Size getSize() const { return m_size; }

protected: 
    // Description/Variables of the Object
    cv::Scalar m_color; 
    Size m_size; 
    Speed m_speed; 
    Position m_position;
};

#endif // GAMEOBJECT_HPP