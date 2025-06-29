#include "Square.hpp"

void Square::draw(cv::Mat& frame) {
    // Ein grünes Rechteck zeichnen:
    cv::rectangle(frame, cv::Rect(m_position.x, m_position.y, m_size.width, m_size.height), m_color, -1);
}

bool Square::checkCollision(const cv::Rect& face) {
    // Prüfen, ob das Quadrat mit dem Gesicht (Rechteck) kollidiert
    cv::Rect squareRect(m_position.x, m_position.y, m_size.width, m_size.height);
    return (squareRect & face).area() > 0; // Schnittmenge der Rechtecke > 0
}
