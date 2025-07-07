#include "Circle.hpp"

void Circle::draw(cv::Mat& frame) {
    cv::circle(frame, m_position, m_size.width / 2, m_color, -1);
}

bool Circle::checkCollision(const cv::Rect& face) {
    int centerX = m_position.x + m_size.width / 2;
    int centerY = m_position.y + m_size.height / 2;
    return (centerX > face.x && centerX < face.x + face.width &&
            centerY > face.y && centerY < face.y + face.height);
}
