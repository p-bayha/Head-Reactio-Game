#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"
#include "GUI.hpp"

/*
 * @brief Handles all user interface interactions
 */
class GUI {
public:
    // Default constructor
    GUI() = default;

    // Default destructor
    ~GUI() = default;

    // Displays the welcome menu in the terminal.
    void displayMenu() const;

    //NEW: shows menu on the screen
    void showMainMenuWindow(std::string& playerName, GameMode& selectedMode);

    // Helperfunction for entering correct name that returns empty string if valid, else returns error message
    std::string validateName(const std::string& name) const;

    // Shows score while playing, add later maybe
    //void GUI::drawHUD(cv::Mat& frame, const Player& player)

    // Prints the player's name and score to the terminal.
    void printPlayerInfo(const Player& player) const;

    // Shows a terminal "Game Over" screen ("Game Over" + ESC can be added as text later)
    void displayGameOver() const;

    // Shows final score and player name
    void displayFinalScore(const Player& player);

private:
    int m_menuframeWidth;
    int m_menuframeHeight;
};

#endif // GUI_HPP