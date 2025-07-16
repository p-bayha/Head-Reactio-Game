
#ifndef CATCHSQUARESMODE_HPP
#define CATCHSQUARESMODE_HPP

#include "GameMode.hpp"
#include "Circle.hpp"
#include "Square.hpp"
#include "GUI.hpp"


// Game mode where the player must catch squares and avoid circles
class CatchSquaresMode : public GameMode {
public:
    // Constructor: initializes the mode with references to the player, GUI, frame dimensions, and total number of objects
    CatchSquaresMode(Player& player, GUI& gui, int frameWidth, int frameHeight, int totalObjects);
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
    int m_spawnTimer;     // Timer for spawning new objects
    int m_remainingObjects; // Number of objects left to spawn
    std::vector<std::shared_ptr<GameObject>> m_objects; // Active objects in the game
};

#endif
