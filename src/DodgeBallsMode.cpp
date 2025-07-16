#include "DodgeBallsMode.hpp"
#include <opencv2/opencv.hpp>

DodgeBallsMode::DodgeBallsMode(Player& player, GUI& gui, int height, int width)
    : m_player(player), m_gui(gui), m_frameHeight(height), m_frameWidth(width) {}

void DodgeBallsMode::initialize() {
    m_player.setScore(0);
    // Weitere Initialisierung hier
}

bool DodgeBallsMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // Hier müsste die Spiellogik rein – für den Moment:
    m_gui.drawGameMode(frame, "Dodge Balls!");
    m_gui.drawScore(frame, m_player.getScore());
    return true; // oder false, um das Spiel zu beenden
}

int DodgeBallsMode::getScore() const {
    return m_player.getScore();
}
