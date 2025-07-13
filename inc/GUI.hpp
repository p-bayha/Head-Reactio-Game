#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>

#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"
#include "constants.hpp"

/*
 * @brief Handles all user interface interactions
 */
class GUI {
public:
    GUI() = default;
    ~GUI() = default;

    // Displays the welcome menu in the terminal.
    void displayMenu() const;

    // Shows the graphical main menu, allowing for players to enter the name and select the game mode
    void showMainMenuWindow(std::string& playerName, GameModeType& selectedMode, int& n_objects);

    // Shows score while playing, add later maybe
    //void GUI::drawHUD(cv::Mat& frame, const Player& player)

    // Returns current mode as string
    std::string getModeString(GameModeType mode) const;

    // Prints the player's name and score to the terminal.
    void printPlayerInfo(const Player& player, GameModeType mode, int n_objects) const;

    // Shows a terminal "Game Over" screen
    void displayGameOver() const;

    // Shows final score and player name
    void displayFinalScore(const Player& player);

    friend class GUITest_ValidateNameRejectsEmpty_Test;
    friend class GUITest_ValidateNameTooLong_Test;
    friend class GUITest_ValidateNameWithInvalidCharacters_Test;
    friend class GUITest_ValidateNameValid_Test;

private: 
    MenuConstants m_menuState;

    void drawMenuUI(cv::Mat& menu, MenuConstants menuState, const std::vector<std::string>& gameModes) const;
    std::string validateName(const std::string& name) const;

    void handleKeyboardInput(int key);
    void handleMouseInput(bool& clicked,int x, int y, const std::vector<cv::Rect>& modeButtons);

    const int m_menuframeWidth = 1280;
    const int m_menuframeHeight = 720;
    const int m_centerX = m_menuframeWidth / 2;
    int m_baseline = 0;

    const int m_screenWidth = 1440;
    const int m_screenHeight = 740;

    const int m_posX = (m_screenWidth - m_menuframeWidth) / 2;
    const int m_posY = (m_screenHeight - m_menuframeHeight) / 2;
};

#endif // GUI_HPP