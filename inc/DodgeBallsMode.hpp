#ifndef DODGEBALLSMODE_HPP
#define DODGEBALLSMODE_HPP

#include "GameMode.hpp"
#include "Circle.hpp"
#include "Player.hpp"

#include "GUI.hpp"
#include <vector>
#include <memory>

// Game mode where the player must dodge falling balls (circles)
class DodgeBallsMode : public GameMode {
public:
    // Constructor: initializes the mode with references to the player, GUI, and frame dimensions
    DodgeBallsMode(Player& player, GUI& gui, int frameWidth, int frameHeight);

    // Resets the game state for a new round
    void initialize() override;

    // Updates the game state, processes collisions, and draws the frame
    bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) override;

    // Returns the current score
    int getScore() const override;

private:
    Player& m_player;      // Reference to the player object
    GUI& m_gui;           // Reference to the GUI for drawing
    int m_frameWidth;     // Width of the game frame
    int m_frameHeight;    // Height of the game frame
    int m_spawnTimer;     // Timer for spawning new balls
    std::vector<std::shared_ptr<Circle>> m_circles; // Active falling balls
};

#endif