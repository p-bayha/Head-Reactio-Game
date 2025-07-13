#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>

#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"

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
    struct MenuState {
        std::string nameInput;
        std::string objectCountInput;
        std::string errorMsg;

        int selectedIndex = 0;
        bool typingName = true;
        bool focusOnObjectCount = false;
        bool confirmed = false;
        bool showCursor = true;
        int frameCount = 0;
        int n_objects = 0;

        GameModeType m_gameMode; 

    } m_menuState;

    void drawMenuUI(cv::Mat& menu, MenuState menuState, const std::vector<std::string>& gameModes) const;
    std::string validateName(const std::string& name) const;

    void handleKeyboardInput(int key);
    void handleMouseInput(bool& clicked,int x, int y, const std::vector<cv::Rect>& modeButtons);

    int m_menuframeWidth = 800;
    int m_menuframeHeight = 600;

    static constexpr int ENTER_KEY = 13;
    static constexpr int ESC_KEY = 27;
    static constexpr int BACKSPACE_KEY = 8;
    static constexpr int MAX_NAME_LENGTH = 30;
    static constexpr int MAX_OBJECT_COUNT_DIGITS = 3;

    const cv::Scalar BG_COLOR = cv::Scalar(30, 30, 30);
    const cv::Scalar TEXT_COLOR = cv::Scalar(255, 255, 255);
    const cv::Scalar ACTIVE_COLOR = cv::Scalar(0, 255, 0);
    const cv::Scalar ERROR_COLOR = cv::Scalar(0, 0, 255);

};

#endif // GUI_HPP