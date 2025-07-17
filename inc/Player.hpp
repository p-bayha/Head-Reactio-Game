#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

/**
 * @brief Represents a single player in the game.
 * The Player class stores the player's name and score. It provides methods to
 * set and retrieve the na,e, as well as tp modify or set the score. 
 * The score is always clamped to be non-negative (it never becomes negative).
 */
class Player {
public:
    Player() = default;
    ~Player() = default;

    /// @brief Sets the player's name
    /// @param name The new name to assign to the player.
    void setName(const std::string& name);

    /// @brief Gets the player's name.
    /// @return The current name of the player.
    std::string getName() const;

    ///@brief Modifies the player's score by a delta value.
    ///@param delta Amount to add or subtract from the score (can be negative).
    void changeScore(int delta);

    /// @brief Sets the player's score directly.
    //         Of the value is negative, it will be clamped to zero.
    /// @param score The new score to assign to the player.
    void setScore(int score);

    /// @brief Gets the current player's score.
    /// @return The player's score.
    int getScore() const; 
    
private:
    std::string m_name {}; // Default initialized empty string
    int m_score = 0; 
};

#endif // PLAYER_HPP