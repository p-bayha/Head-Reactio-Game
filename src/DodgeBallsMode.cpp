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
    // Neue Kreise erzeugen
    if (++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30); // zufällige Größe
        float speed = 3.0f + static_cast<float>(std::rand() % 40) / 10.0f; // zufällige Geschwindigkeit
        cv::Point pos(std::rand() % m_frameWidth, 0);

        // Zufällige Farbe (rot, blau, grün)
        cv::Scalar color;
        int c = std::rand() % 3;
        if (c == 0) color = cv::Scalar(0,0,255);
        else if (c == 1) color = cv::Scalar(255,0,0);
        else color = cv::Scalar(0,255,0);

        m_circles.push_back(std::make_shared<Circle>(color, Size{size,size}, Speed{speed}, pos));
    }

    // Alle Kreise bewegen, zeichnen und prüfen
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
            // Für 3 Sekunden GAME OVER anzeigen
            m_gui.drawGameOver(frame);
            cv::imshow("Game Window", frame);
            cv::waitKey(3000);
            return false; // Spiel beenden
        }

        // Punktestand erhöhen, wenn Kreis unten angekommen ist
        if (circle->getPosition().y > m_frameHeight) {
            m_player.changeScore(1);
            it = m_circles.erase(it);
        } else {
            ++it;
        }
    }

    // Anzeige für Spieler
    m_gui.drawGameMode(frame, "Dodge the Balls!");
    m_gui.drawScore(frame, m_player.getScore());

    return true; // Spiel läuft weiter
}

int DodgeBallsMode::getScore() const {
    return m_player.getScore();
}