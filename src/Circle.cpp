#include "Circle.hpp"

void Circle::move() {
    m_position.y += static_cast<int>(m_speed.y);
}
#include "Circle.hpp"

void Circle::draw(cv::Mat& frame) {
    cv::circle(frame, cv::Point(m_position.x, m_position.y), m_size.width / 2, m_color, -1);
}

bool Circle::checkCollision(const cv::Rect& face) {
    return intersects(face);
}

bool Circle::intersects(const cv::Rect& face) {
    cv::Point center(m_position.x, m_position.y);
    int radius = m_size.width / 2;

    // Approximate bounding box of the circle
    cv::Rect circleRect(center.x - radius, center.y - radius, radius * 2, radius * 2);
    return (circleRect & face).area() > 0;
}