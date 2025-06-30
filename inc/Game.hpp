#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GUI.hpp"

// Nachher in game mode
enum class GameMode {
    DodgeBalls = 1,
    CatchSquares = 2
};

/*
 * @brief Main controller class. 
 Manages player setup, game loop, face detection, GUI update and scoring.
 */
class Game {
public:
    // Constructor with path to Haar cascade 
    Game(const std::string& cascadePath);

    // Default destructor
    ~Game() = default;

    // Start the game (setup, initialization, etc.)
    void startGame();

private:
    // Initializes player (name, mode)
    void setupPlayer();

    // Core game loop (face detection and gameplay)
    void gameLoop();

    // Ends the game (showa final results etc.)
    void endGame();

    // int updateScore(int points); maybe later or GUI/Player


    Player m_player;
    FaceDetector m_faceDetector;
    GUI m_gui;
    int m_gameMode; // wenn Game Mode implitiert ist, current game mode (1 or 2)
    bool m_gameRunning; // Controls game loop

};

#endif // GAME_HPP