#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <memory> 
#include <opencv2/opencv.hpp>

#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"
#include "GUI.hpp"

/*
 * @brief Main controller class. 
 Manages player setup, game loop, face detection, GUI update and scoring.
 */
class Game {
public:
    // Constructor with path to Haar cascade file
    Game(const std::string& cascadePath);

    ~Game() = default;

    // Start the game: setup, initialization and main loop
    void startGame();

    void enableTestMode() { m_testMode = true; }

    // Needed for testing
    std::string getPlayerName() const { return m_player.getName(); }
    bool isGameRunning() const { return m_gameRunning; }
    
private:
    // Setup player: name, game mode and initialize game mode instance
    void setupPlayer();

    // Main game loop: process frames, update gameplay, render GUI
    void gameLoop();

    // End the game: display final results and clean up
    void endGame();

    // Spawn and update game objects during gameplay
    void spawnObjects(); 
    void updateObjects(cv::Mat& frame, const std::vector<cv::Rect>& faces);

    Player m_player;
    FaceDetector m_faceDetector;
    GUI m_gui;

    GameModeType m_gameMode; // Current game mode
    std::unique_ptr<GameMode> m_gameModePtr; // Polymorphic pointer to active game mode implementation

    bool m_gameRunning = false; // Controls the main game loop
    bool m_testMode = false; // Skip GUI in tests

    std::vector<std::shared_ptr<GameObject>> objects; // Active game object in the scene

    int spawnTimer = 0; // Timer for spawning new objects
    int mode = 1; // Default mode
};

#endif // GAME_HPP

