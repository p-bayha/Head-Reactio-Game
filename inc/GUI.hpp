#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>
#include "Player.hpp"
#include "FaceDetector.hpp"

/*
 * @brief Handles all user interface interactions
 */
class GUI {
public:
    // Default constructor
    GUI() = default;

    // Default destructor
    ~GUI() = default;

    // Displays the menu in the terminal.
    void displayMenu() const;

    /// @brief Prompts the user to input their name via terminal.
    /// @return playerName
    std::string inputName();

    // Prints the player's name and score to the terminal.
    void printPlayerInfo(const Player& player) const;

    /// @brief Asks GameMode from player.
    /// @return GameMode (1 or 2)
    int askGameMode() const;

    /// @brief Shows game window including objects and score
    /// @note braucht noch parameter wie Kamera-Frame, Gesichtsposition etc.
    void displayGameWindow(FaceDetector& detector);

    // shows GameOver window (f.g. "Game Over" + ESC)
    void displayGameOver() const;

    // Shows final score and player name
    void displayFinalScore(const Player& player);
};

#endif // GUI_HPP