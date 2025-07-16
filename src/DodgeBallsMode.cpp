#include "DodgeBallsMode.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GUI.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>

DodgeBallsMode::DodgeBallsMode(Player& player, GUI& gui, int m_frameWidth, int m_frameHight)
    : m_player(player), m_gui(gui), m_frameWidth(m_frameWidth), m_frameHeight(m_frameHight), m_spawnTimer(0) {}

void DodgeBallsMode::initialize() {
    m_player.setScore(0);
    m_circles.clear();
    m_spawnTimer = 0;
}

bool DodgeBallsMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // Create new circles
    if (++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30); // random size
        float speed = 6.0f + static_cast<float>(std::rand() % 60) / 10.0f; // random speed
        cv::Point pos(std::rand() % m_frameWidth, 0);

        // random color (red, blue, green)
        cv::Scalar color;
        int c = std::rand() % 3;
        if (c == 0) color = cv::Scalar(0,0,255);
        else if (c == 1) color = cv::Scalar(255,0,0);
        else color = cv::Scalar(0,255,0);

        m_circles.push_back(std::make_shared<Circle>(color, Size{size,size}, Speed{speed}, pos));
    }

    // Move all circles, draw and check
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
            // Display GAME OVER for 3 seconds
            m_gui.drawGameOver(frame, m_player);
            cv::imshow("Game Window", frame);
            cv::waitKey(3000);
            return false; // ends game
        }

        // Increase score when circle reaches the bottom
        if (circle->getPosition().y > m_frameHeight) {
            m_player.changeScore(1);
            it = m_circles.erase(it);
        } else {
            ++it;
        }
    }

    // Display for player
    m_gui.drawGameMode(frame, "Dodge the Balls!");
    m_gui.drawScore(frame, m_player.getScore());

    return true; // Game continues
}

int DodgeBallsMode::getScore() const {
    return m_player.getScore();
}
