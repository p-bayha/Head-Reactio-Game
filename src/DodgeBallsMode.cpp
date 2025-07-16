

#include "DodgeBallsMode.hpp"
#include "Circle.hpp"
#include <opencv2/opencv.hpp>
#include <memory>
#include <vector>
#include <cstdlib>


DodgeBallsMode::DodgeBallsMode(Player& player, GUI& gui, int frameWidth, int frameHeight)
    : m_player(player), m_gui(gui), m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_spawnTimer(0) {}

void DodgeBallsMode::initialize() {
    m_player.setScore(0);
    m_circles.clear();
    m_spawnTimer = 0;
}

bool DodgeBallsMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // Spawn a new ball every 20 frames
    if (++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30);
        float speed = 6.0f + static_cast<float>(std::rand() % 60) / 10.0f;
        cv::Point pos(std::rand() % m_frameWidth, 0);
        cv::Scalar color;
        int c = std::rand() % 3;
        if (c == 0) color = cv::Scalar(0,0,255);
        else if (c == 1) color = cv::Scalar(255,0,0);
        else color = cv::Scalar(0,255,0);
        m_circles.push_back(std::make_shared<Circle>(color, Size{size,size}, Speed{speed}, pos));
    }

    // Move, draw, and check all balls
    for (auto it = m_circles.begin(); it != m_circles.end();) {
        auto& circle = *it;
        circle->move();
        circle->draw(frame);

        bool hit = false;
        for (const auto& face : faces) {
            if (circle->checkCollision(face)) {
                hit = true;
                break;
            }
        }
        if (hit) {
            m_gui.drawGameOver(frame, m_player);
            cv::imshow("Game Window", frame);
            cv::waitKey(3000);
            return false;
        }
        if (circle->getPosition().y > m_frameHeight) {
            m_player.changeScore(1);
            it = m_circles.erase(it);
        } else {
            ++it;
        }
    }

    m_gui.drawGameMode(frame, "Dodge Balls!");
    m_gui.drawScore(frame, m_player.getScore());
    return true;
}

int DodgeBallsMode::getScore() const {
    return m_player.getScore();
}
