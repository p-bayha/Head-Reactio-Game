#include "Game.hpp"
#include "DodgeBallsMode.hpp"
#include "CatchSquaresMode.hpp"
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>

// Constructor
Game::Game(const std::string& cascadePath) : m_faceDetector(cascadePath), m_gameMode(GameModeType::None), m_gameRunning(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }


// Starts game
void Game::startGame() {
    // Show menu and setup player name in the terminal
    m_gui.displayMenu();
    
    // m_gui.drawHUD(cv::Mat& frame, const Player& player, GameMode mode); 

    setupPlayer();

    // Now it should also call display menu window

    // Initializes FaceDetector
    if (!m_faceDetector.initialize()) {
        std::cerr << "Error initializing FaceDetector.\n";
        return;
    }

    if(!m_faceDetector.isInitialized()) {
        std::cerr << "Detector not ready." << std::endl;
        return;
    }

    m_gameRunning = true;

    gameLoop(); // Start game loop
    endGame(); 
}

// Setup-Phase: asking for player name and game mode
void Game::setupPlayer() {
    std::string name;
    GameModeType mode;
    int n_objects = 0;
    m_gui.showMainMenuWindow(name, mode, n_objects);

    m_player.setName(name);

    // Choose game mode (later part of game mode class)
    m_gameMode = mode;

    //std::unique_ptr<GameMode> m_gameModePtr;
    
    if (mode == GameModeType::CatchSquares) {
        m_gameModePtr = std::make_unique<CatchSquaresMode>(m_player, 640, 480, n_objects);
    } else if (mode == GameModeType::DodgeBalls) {
        m_gameModePtr = std::make_unique<DodgeBallsMode>(m_player, 640, 480);
    }

    // Show player information
    m_gui.printPlayerInfo(m_player, m_gameMode, n_objects);
}

// Main game loop 
void Game::gameLoop() {
    const std::string windowName = "Game Window";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    /* Inhalt der GUI im Menu
      while (mode != 1 && mode != 2) {
        std::cout << "Select mode (1 = Dodge the balls, 2 = Catch the squares): ";
        std::cin >> mode;
        if (mode != 1 && mode != 2) {
            std::cout << "Invalid mode, please enter 1 or 2." << std::endl;
        }
    } */
     // if (!initialize()) return;
    if(!m_gameModePtr) {
        std::cerr << "Error: Game mode pointer is not initialized!" << std::endl;
        return;
    }

    m_gameModePtr->initialize();

    /*
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);

        
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        } */

    while(m_gameRunning) {
        cv::Mat frame = m_faceDetector.getProcessedFrame();

        if (frame.empty()) {
            std::cerr << "Error: Empty frame recieved.\n" << std::endl;
            break;
        }

        std::vector<cv::Rect> faces = m_faceDetector.detectFaces(frame);

        if (!m_gameModePtr->update(frame, faces)) {
            break;
        }

        // Display the frame

        cv::imshow(windowName, frame);

        // Exit loop if ESC key (ASCII 27) is pressed 
        int key = cv::waitKey(10);

        if (key == 27) {
            m_gameRunning = false; 
        }
    }

    cv::destroyWindow(windowName);
}

// Ends the game 
void Game::endGame() {
    m_gui.displayGameOver();
    m_gui.displayFinalScore(m_player);
}

