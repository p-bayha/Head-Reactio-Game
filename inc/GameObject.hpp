#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <opencv2/opencv.hpp>
#include "Utils.hpp"

class GameObject {
public:
    GameObject(cv::Scalar color, Size size, Speed speed, Position pos)
        : m_color(color), m_size(size), m_speed(speed), m_position(pos) {}

    virtual ~GameObject() = default;

    // Move the object by its speed (default: do nothing, override in derived)
    virtual void move() = 0;

    virtual void draw(cv::Mat& frame) = 0;
    virtual bool checkCollision(const cv::Rect& face) = 0;

    Position getPosition() const { return m_position; }
    Size getSize() const { return m_size; } // <-- NEU

protected:
    cv::Scalar m_color;
    Size m_size;
    Speed m_speed;
    Position m_position;
};

#endif // GAMEOBJECT_HPP