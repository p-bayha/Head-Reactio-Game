#include "Player.hpp"
#include <iostream>

//Sets the player's name
void Player::setName(const std::string& input) {
    m_name = input;
}

// Returns the player's name
std::string Player::getName() const {
    return m_name;
}

// Adjusts the score by a given delta, clamping it to zero if necessary 
void Player::changeScore(int delta) {
    m_score += delta;
    if (m_score < 0) {
        m_score = 0;
    }
}

//Set the player's score directly, clamping it to zero if negative
void Player::setScore(int score) {
    if (score < 0) {
        std::cerr << "[Warning] Tried to set negative score (" << score << "). Clamping to 0." << std::endl;
    }
    m_score = (score >= 0) ? score : 0;
}

// Returns the player's current score
int Player::getScore() const {
    return m_score;
}

