#include "Game.hpp"
#include <iostream>
#include "FaceDetector.hpp"

// Constructor
Game::Game(const std::string& cascadePath) : m_faceDetector(cascadePath), m_gameMode(0), m_gameRunning(false) {}

// Starts game
void Game::startGame()
{
    m_gui.displayMenu();
    setupPlayer();

    // Initializes FaceDetector
    if (!m_faceDetector.initialize()) {
        std::cerr << "Error initializing FaceDetector.\n";
        return;
    }

    std::cout << "\nStarting game in mode " << m_gameMode << "...\n" << std::endl;
    m_gameRunning = true;

    gameLoop(); // Start game loop
    endGame(); 
}

// Setup-Phase: asking for player name and game mode
void Game::setupPlayer() {
    std::string name = m_gui.inputName();
    m_player.setName(name);

    m_gameMode = m_gui.askGameMode();

    m_gui.printPlayerInfo(m_player);
}

// Main game loop (Placeholder)
void Game::gameLoop() {
    const std::string windowName = "Game Window";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    while(m_gameRunning) {
        cv::Mat frame = m_faceDetector.getProcessedFrame();

        if (frame.empty()) {
            std::cerr << "Error: Empty frame recieved.\n" << std::endl;
            break;
        }

        // TODO: GameMode-Logik abhängig von m_gameMode noch einbauen
        // Punktevergabe, Zeit, Reaktion, etc.

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