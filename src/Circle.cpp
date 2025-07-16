#include "Circle.hpp"

//Moves the circle down by its speed
void Circle::move() {
    m_position.y += static_cast<int>(m_speed.y);
}

//Draws the circle on the given frame.
void Circle::draw(cv::Mat& frame) {
    cv::circle(frame, cv::Point(m_position.x, m_position.y), m_size.width / 2, m_color, -1);
}

//Checks if the circle collides with a given rectangle (face)
bool Circle::checkCollision(const cv::Rect& face) {
    return intersects(face);
}

//Checks if the circle's bounding box intersects with a rectangle
bool Circle::intersects(const cv::Rect& face) {
    cv::Point center(m_position.x, m_position.y);
    int radius = m_size.width / 2;

    // Approximate bounding box of the circle
    cv::Rect circleRect(center.x - radius, center.y - radius, radius * 2, radius * 2);
    return (circleRect & face).area() > 0;
}