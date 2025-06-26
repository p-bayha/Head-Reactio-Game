#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>

/**
 * @brief Represents a single player in the game.
 * Stores the player's name and score and provides methods to access and update them.
 */
class Player {
public:
    // Default constructor
    Player() = default;

    // Default destructor
    ~Player() = default;

    // Prompts the user to input their name via terminal.
    void inputName();

    /// @brief Sets the player's name
    /// @param name The new name for the player.
    void setName(const std::string& name);

    // Returns the player's name.
    std::string getName() const;

    ///@brief Changes the player's score.
    ///@param delta Score change (can be negative).
    void changeScore(int delta);

    /// @brief Sets the player's score directly.
    //         Score will be reduced to zero if a negative value is passed.
    /// @param score The new score value.
    void setScore(int score);

    // Gets the player's score.
    int getScore() const;

    // Prints the player's name and score to the terminal.
    void printPlayerInfo() const;

private:
    std::string m_name {}; // Default initialized empty string
    int m_score = 0; 
};

#endif // PLAYER_HPP