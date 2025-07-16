


// Implements the DodgeBalls game mode where the player must avoid falling balls (circles)
#include "DodgeBallsMode.hpp"
#include "Circle.hpp"
#include <opencv2/opencv.hpp>
#include <memory>
#include <vector>
#include <cstdlib>

// Constructor: initializes references and game state
DodgeBallsMode::DodgeBallsMode(Player& player, GUI& gui, int frameWidth, int frameHeight)
    : m_player(player), m_gui(gui), m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_spawnTimer(0) {}

// Resets the game state for a new round
void DodgeBallsMode::initialize() {
    m_player.setScore(0);
    m_circles.clear();
    m_spawnTimer = 0;
}

// Updates the game state: spawns, moves, draws balls, checks for collisions and scoring
bool DodgeBallsMode::update(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    // Spawn a new ball every 20 frames
    if (++m_spawnTimer >= 20) {
        m_spawnTimer = 0;
        int size = 20 + (std::rand() % 30); // Random ball size
        float speed = 6.0f + static_cast<float>(std::rand() % 60) / 10.0f; // Random fall speed
        cv::Point pos(std::rand() % m_frameWidth, 0); // Random horizontal position at top
        cv::Scalar color;
        int c = std::rand() % 3;
        if (c == 0) color = cv::Scalar(0,0,255); // Red
        else if (c == 1) color = cv::Scalar(255,0,0); // Blue
        else color = cv::Scalar(0,255,0); // Green
        m_circles.push_back(std::make_shared<Circle>(color, Size{size,size}, Speed{speed}, pos));
    }

    // Move, draw, and check all balls for collision or if they leave the screen
    for (auto it = m_circles.begin(); it != m_circles.end();) {
        auto& circle = *it;
        circle->move(); // Move ball downwards
        circle->draw(frame); // Draw ball

        bool hit = false;
        // Check collision with any detected face
        for (const auto& face : faces) {
            if (circle->checkCollision(face)) {
                hit = true;
                break;
            }
        }
        if (hit) {
            // End game if player is hit
            m_gui.drawGameOver(frame, m_player);
            cv::imshow("Game Window", frame);
            cv::waitKey(3000);
            return false;
        }
        // Remove ball and increase score if it leaves the screen
        if (circle->getPosition().y > m_frameHeight) {
            m_player.changeScore(1);
            it = m_circles.erase(it);
        } else {
            ++it;
        }
    }

    // Draw game mode and score for player
    m_gui.drawGameMode(frame, "Dodge Balls!");
    m_gui.drawScore(frame, m_player.getScore());
    return true;
}

// Returns the current score
int DodgeBallsMode::getScore() const {
    return m_player.getScore();
}
