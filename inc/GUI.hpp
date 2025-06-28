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

    // Displays the welcome menu in the terminal.
    void displayMenu() const;

    /// @brief Prompts the user to input their name via terminal.
    /// @return name
    std::string inputName();

    // Prints the player's name and score to the terminal.
    void printPlayerInfo(const Player& player) const;

    /// @brief Let's the player choose the game mode.
    /// @return Chosen game mode (1 or 2)
    int askGameMode() const;

    /// @brief Shows game window including objects (in the future) and score
    /// @param detector FaceDetector instance passed by reference.
    void displayGameWindow(FaceDetector& detector);

    // Shows a terminal "Game Over" screen ("Game Over" + ESC can be added as text later)
    void displayGameOver() const;

    // Shows final score and player name
    void displayFinalScore(const Player& player);
};

#endif // GUI_HPP