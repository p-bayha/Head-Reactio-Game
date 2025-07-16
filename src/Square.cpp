#include "Square.hpp"

void Square::move() {
    m_position.y += static_cast<int>(m_speed.y);
}
#include "Square.hpp"

void Square::draw(cv::Mat& frame) {
    // Draw a green rectangle representing the square
    cv::rectangle(frame, cv::Rect(m_position.x, m_position.y, m_size.width, m_size.height), m_color, -1);
}

bool Square::checkCollision(const cv::Rect& face) {
    // Check if the square collides with the face (rectangle)
    cv::Rect squareRect(m_position.x, m_position.y, m_size.width, m_size.height);
    // Return true if the intersection area of the two rectangles is greater than 0
    return (squareRect & face).area() > 0;
}
