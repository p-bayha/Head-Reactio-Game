#include "Game.hpp"
#include "Player.hpp"
#include "DodgeBallsMode.hpp"
#include "CatchSquaresMode.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "FaceDetector.hpp"
#include <memory>

// Constructor
Game::Game(const std::string& cascadePath) : m_faceDetector(cascadePath), m_gameMode(GameMode::None), m_gameRunning(false), frameWidth(0), frameHeight(0) {
    faceCascade.load(cascadePath);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }


// Starts game
void Game::startGame()
{
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

      if (faceCascade.empty()) {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    std::cout << "\nStarting game in mode " << getModeString() << "...\n" << std::endl;
    m_gameRunning = true;

    gameLoop(); // Start game loop
    endGame(); 
}

std::string Game::getModeString() const {
    // Auch Teil der Game mode klasse, nachher evtl. anders umgesetzt
    std::string modeString;
    switch (m_gameMode) {
        case GameMode::DodgeBalls: 
            modeString = "Dodge Balls";
            break;
        case GameMode::CatchSquares: 
            modeString = "Catch Squares";
            break;
        // evtl. nachher noch weitere modes
        default: 
            modeString = "Unknown";
            break;

    }
    return modeString;
}
// Setup-Phase: asking for player name and game mode
void Game::setupPlayer() {
    std::string name;
    GameMode mode;
    m_gui.showMainMenuWindow(name, mode);

    m_player.setName(name);

    // Choose game mode (later part of game mode class)
    m_gameMode = mode;

    // Show player information
    m_gui.printPlayerInfo(m_player);
}

// Main game loop 
void Game::gameLoop() {
    const std::string windowName = "Game Window";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

      while (mode != 1 && mode != 2) {
        std::cout << "Select mode (1 = Dodge the balls, 2 = Catch the squares): ";
        std::cin >> mode;
        if (mode != 1 && mode != 2) {
            std::cout << "Invalid mode, please enter 1 or 2." << std::endl;
        }
    }
      if (!initialize()) return;

    std::unique_ptr<GameMode> gameMode;

    if (mode == 1) {
        gameMode = std::make_unique<DodgeBallsMode>(player, frameWidth, frameHeight);
    } else if (mode == 2) {
        int n;
        std::cout << "Enter number of objects (N): ";
        std::cin >> n;
        gameMode = std::make_unique<CatchSquaresMode>(player, frameWidth, frameHeight, n);
    }

    gameMode->initialize();

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        if (!gameMode->update(frame, faces)) {
            break;
        }
    while(m_gameRunning) {
        cv::Mat frame = m_faceDetector.getProcessedFrame();

        if (frame.empty()) {
            std::cerr << "Error: Empty frame recieved.\n" << std::endl;
            break;
        }

        // TODO: GameMode-Logik abhängig von m_gameMode noch einbauen
        // Punktevergabe, Zeit, Reaktion, etc.

        // NEW: GUI shows score on the screen
        //m_gui.drawHUD(frame, m_player, m_gameMode);

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

