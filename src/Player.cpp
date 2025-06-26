#include "Player.hpp"
#include <iostream>

// Prompts the user to input their name via terminal
void Player::inputName() {
    std::string input;
    while (true) {
        std::cout << "Enter your name: ";
        std::getline(std::cin, input); //Gets the full name, not just one word

        // Check length
        if (input.length() < 2 || input.length() > 30) {
            std::cout << "Invalid length. Name must be between 2 and 30 characters.\n";
            continue;
        }

        // Check if only alphabetic characters or spaces are used
        bool valid = true;
        for (char c : input) {
            if (!std::isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid characters. Only letters and spaces allowed.\n";
            continue;
        }

        // Valid name
        m_name = input;
        break;
    }
}

//Sets the player's name
void Player::setName(const std::string& name) {
    m_name = name;
}

// Returns the player's name
std::string Player::getName() const {
    return m_name;
}

//Change the player's score 
void Player::changeScore(int delta) {
    m_score += delta;
    if (m_score < 0) {
        m_score = 0;
    }
}

//Set the player's score (never below zero)
void Player::setScore(int score) {
    if (score < 0) {
        std::cerr << "[Warning] Attempted to set negative score (" << score << "). Clamping to 0." << std::endl;
    }
    m_score = (score >= 0) ? score : 0;
}

// Get the player's score
int Player::getScore() const {
    return m_score;
}

// Print the player's name and score
void Player::printPlayerInfo() const {
    std::cout << "Playername: " << m_name << "\nScore: " << m_score << std::endl;
}
