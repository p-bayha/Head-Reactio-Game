#include "CatchSquaresMode.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include <cstdlib>
#include <opencv2/opencv.hpp>

CatchSquaresMode::CatchSquaresMode(Player& player, GUI& gui, int frameHight, int frameWidth, int totalObjects)
    : m_player(player), m_gui(gui), m_frameWidth(frameWidth), m_frameHeight(frameHight),
      m_spawnTimer(0), m_remainingObjects(totalObjects) {
      }

void CatchSquaresMode::initialize() {
    m_player.setScore(0);
    m_objects.clear();
    m_spawnTimer = 0;
}

bool CatchSquaresMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // As long as there are objects left to spawn, generate new objects every 20 frames
    if (m_remainingObjects > 0 && ++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30);
        float speed = 3.0f + static_cast<float>(std::rand() % 40) / 10.0f;
        cv::Point pos(std::rand() % m_frameWidth, 0);

        // Randomly spawn either a red circle or a green square at the top
        if (std::rand() % 2 == 0) {
            m_objects.push_back(std::make_shared<Circle>(cv::Scalar(0,0,255), Size{size,size}, Speed{speed}, pos));
        } else {
            m_objects.push_back(std::make_shared<Square>(cv::Scalar(0,255,0), Size{size,size}, Speed{speed}, pos));
        }
        --m_remainingObjects; // Decrease the number of objects left to spawn
    }

    // Move, draw, and check all objects for collisions or if they leave the screen
    for (auto it = m_objects.begin(); it != m_objects.end();) {
        auto& obj = *it;
        obj->move(); // Move object downwards
        obj->draw(frame); // Draw object on the frame

        bool collided = false;
        // Check collision with any detected face
        for (const auto& face : faces) {
            if (obj->checkCollision(face)) {
                // If a circle is caught, decrease score; if a square is caught, increase score
                if (dynamic_cast<Circle*>(obj.get())) {
                    m_player.changeScore(-1); // Penalty for catching a circle
                } else if (dynamic_cast<Square*>(obj.get())) {
                    m_player.changeScore(1); // Reward for catching a square
                }
                collided = true;
                break;
            }
        }

        // Remove object if it collided or moved out of the frame
        if (collided || obj->getPosition().y > m_frameHeight) {
            it = m_objects.erase(it);
        } else {
            ++it;
        }
    }

    // Display game mode and current score for the player
    m_gui.drawGameMode(frame, "Catch the Squares!");
    m_gui.drawScore(frame, m_player.getScore());

    // End the game only when all objects have been spawned and all are gone
    return !(m_remainingObjects <= 0 && m_objects.empty());
}

int CatchSquaresMode::getScore() const {
    return m_player.getScore();
}
