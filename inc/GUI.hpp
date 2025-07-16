#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>

#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"
#include "constants.hpp"

/**
 * @brief Handles all user interface interactions:
 * Console output, GUI-based menu and gameplay HUD drawing.
 */
 
class GUI {
public:
    GUI() = default;
    ~GUI() = default;

    // Displays a welcome message and menu navigation instructions.
    void displayMenu() const;

    // Displays the final player name and score in the terminal.
    void printPlayerInfo(const Player& player, GameModeType mode, int objectCount) const;

    // Displays "Game Over" text in the terminal.
    void displayGameOver() const;

    // Displays final score and player name in terminal.
    void displayFinalScore(const Player& player);


    // Show the graphical main menu, allowing for players to enter the name and select the game mode
    void showMainMenuWindow(std::string& playerName, GameModeType& selectedMode, int& n_objects);

    // Displays the current game mode name.
    void drawGameMode(cv::Mat& frame, std::string currentGameMode);

    // Displays the player's score.
    void drawScore(cv::Mat& frame, int score) const;

    // Displays "GAME OVER" on the gameplay screen.
    void drawGameOver(cv::Mat& frame);

    // Utility. (public for testing), validates the entered player name.
    std::string validateName(const std::string& name) const;

private: 
    // Input handlers (Keyboard and Mouse)
    void handleKeyboardInput(int key);
    void handleMouseInput(bool& clicked,int x, int y, const std::vector<cv::Rect>& modeButtons);

    // GUI drawing utilities
    void drawTitle(cv::Mat& menuFrame);
    void drawNameInput(cv::Mat& menuFrame);
    void drawGameModeButtons(cv::Mat& menuFrame, std::vector<std::string> gameModes, std::vector<cv::Rect>& modeButtons);
    void drawErrorMessage(cv::Mat& menuFrame, std::vector<std::string> gameModes, std::vector<cv::Rect>& modeButtons);
    void drawInstructions(cv::Mat& menuFrame);

    // Utility
    std::string getModeString(GameModeType mode) const;

    // Internal State for Menu UI
    MenuConstants m_menuState;

    // UI layout configuration
    static constexpr int m_menuframeWidth = 1280;
    static constexpr int m_menuframeHeight = 720;
    static constexpr int m_screenWidth = 1440;
    static constexpr int m_screenHeight = 740;
    static constexpr int m_centerX = m_menuframeWidth / 2;

    int m_baseline = 0;

    static constexpr int m_posX = (m_screenWidth - m_menuframeWidth) / 2;
    static constexpr int m_posY = (m_screenHeight - m_menuframeHeight) / 2;
};

#endif // GUI_HPP