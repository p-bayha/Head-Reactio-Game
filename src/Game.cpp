#include "Game.hpp"
#include "DodgeBallsMode.hpp"
#include "CatchSquaresMode.hpp"
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "constants.hpp"

// Constructor initialize FaceDetector with given cascade path, set initial game state
Game::Game(const std::string& cascadePath) : m_faceDetector(cascadePath), m_gameMode(GameModeType::None), m_gameRunning(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

// Starts the game: show menu, setup player, initialize face detector, runs main loop
void Game::startGame() {

    if (!m_testMode) { 
        // Display main menu and get player input
        m_gui.displayMenu();

        setupPlayer();
    } else {
        // testing only: Skip GUI and initialize a dummy/game mode.
        m_player.setName("TestPlayer");
        m_gameMode = GameModeType::DodgeBalls;
        m_gameModePtr = std::make_unique<DodgeBallsMode>(m_player, m_gui, 640, 680);
    }

    // Initializes FaceDetector and verify success
    if (!m_faceDetector.initialize()) {
        std::cerr << "[Error] Failed to initialize FaceDetector.\n";
        return;
    }

    if(!m_faceDetector.isInitialized()) {
        std::cerr << "[Error] FaceDetector not ready after initialization.\n";
        return;
    }

    m_gameRunning = true;

    gameLoop(); // Run main game loop
    endGame(); // Show end game screen and final score
}

// Setup-Phase: ask player for name, game mode and initialize the appropriate game mode instance
void Game::setupPlayer() {
    std::string playerName;
    GameModeType selectedMode;
    int numObjects = 0;

    // Open main menu GUI window to get player name, mode and optional object count
    m_gui.showMainMenuWindow(playerName, selectedMode, numObjects);

    m_player.setName(playerName);
    m_gameMode = selectedMode;
    
    // Initialize game mode instance based on selected mode
    if (selectedMode == GameModeType::CatchSquares) {
        m_gameModePtr = std::make_unique<CatchSquaresMode>(m_player, m_gui, 640, 480, numObjects);
    } else if (selectedMode == GameModeType::DodgeBalls) {
        m_gameModePtr = std::make_unique<DodgeBallsMode>(m_player, m_gui, 640, 480);
    } else {
        std::cerr << "[Warning] Unknown game mode selected.\n";
    }

    m_gui.printPlayerInfo(m_player, m_gameMode, numObjects);
}

// Main game loop: captures frames, detacts faces, updates game state and renders output
void Game::gameLoop() {
    const std::string windowName = "Game Window";
    const int windowPosX = 80, windowPosY = 10;

    // Skip window creation during testing
    if (!m_testMode) {
        cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        cv::moveWindow(windowName, windowPosX, windowPosY);
    }

    if(!m_gameModePtr) {
        std::cerr << "[Error] Game mode is not initialized!\n";
        return;
    }

    m_gameModePtr->initialize();

    int iterations = 0; // for testing

    while(m_gameRunning) {
        cv::Mat frame = m_faceDetector.getProcessedFrame();

        if (frame.empty()) {
            std::cerr << "[Error] Received empty frame from FaceDetector.\n";
            break;
        }

        std::vector<cv::Rect> detectedFaces = m_faceDetector.detectFaces(frame);

        // Update fame state, if update returns false, end game loop
        if (!m_gameModePtr->update(frame, detectedFaces)) {
            break;
        }

        if (!m_testMode) {
            cv::imshow(windowName, frame);

            int keyPressed = cv::waitKey(10);
            if (keyPressed == ESC_KEY) {
                m_gameRunning = false; 
            }
        }

        if (m_testMode && ++iterations > 1) { // Exit early in tests
            m_gameRunning = false;
        }
    }

    // Close window only if GUI was shown
    if (!m_testMode) {
        cv::destroyWindow(windowName);
    }
    
}

// End game sequence: show game over screen and final player score
void Game::endGame() {
    m_gui.displayGameOver();
    m_gui.displayFinalScore(m_player);
}

