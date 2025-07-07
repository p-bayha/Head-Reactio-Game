#include "CatchSquaresMode.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>

CatchSquaresMode::CatchSquaresMode(Player& player, int m_frameHight, int m_frameWidth, int totalObjects)
    : m_player(player), m_frameWidth(m_frameHight), m_frameHeight(m_frameHight),
      m_spawnTimer(0), m_remainingObjects(totalObjects) {
      }

void CatchSquaresMode::initialize() {
    m_player.setScore(0);
    m_objects.clear();
    m_spawnTimer = 0;
}

bool CatchSquaresMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // Solange noch N übrig, neue Objekte generieren
    if (m_remainingObjects > 0 && ++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30);
        float speed = 3.0f + static_cast<float>(std::rand() % 40) / 10.0f;
        cv::Point pos(std::rand() % m_frameWidth, 0);

        if (std::rand() % 2 == 0) {
            m_objects.push_back(std::make_shared<Circle>(cv::Scalar(0,0,255), Size{size,size}, Speed{speed}, pos));
        } else {
            m_objects.push_back(std::make_shared<Square>(cv::Scalar(0,255,0), Size{size,size}, Speed{speed}, pos));
        }
        --m_remainingObjects;
    }

    // Alle Objekte bewegen, zeichnen und prüfen
    for (auto it = m_objects.begin(); it != m_objects.end();) {
        auto& obj = *it;
        obj->move();
        obj->draw(frame);

        bool collided = false;
        for (const auto& face : faces) {
            if (obj->checkCollision(face)) {
                if (dynamic_cast<Circle*>(obj.get())) {
                    m_player.changeScore(-1);
                } else if (dynamic_cast<Square*>(obj.get())) {
                    m_player.changeScore(1);
                }
                collided = true;
                break;
            }
        }

        if (collided || obj->getPosition().y > m_frameHeight) {
            it = m_objects.erase(it);
        } else {
            ++it;
        }
    }

    // Anzeige oben
    cv::putText(frame, "Catch the Squares!", cv::Point(10,30),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,255,255), 2);
    cv::putText(frame, "Score: " + std::to_string(m_player.getScore()),
                cv::Point(10,70), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(255,255,255), 2);

    // Ende nur wenn N erreicht und alle Objekte weg
    return !(m_remainingObjects <= 0 && m_objects.empty());
}

int CatchSquaresMode::getScore() const {
    return m_player.getScore();
}
