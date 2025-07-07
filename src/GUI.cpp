#include "GUI.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "Game.hpp"

// Display the welcome menu
void GUI::displayMenu() const {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Welcome to the Head Reaction Game " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    // TO DO: Weiterer Inhalt des Menu wie Erklärung und co.
} 

/*void GUI::drawHUD(cv::Mat& frame, const Player& player) {
    std::string info = "Score: " + std::to_string(player.getScore());
    cv::putText(frame, info, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);
} */ // Shows score while playing, add later maybe

void GUI::showMainMenuWindow(std::string& playerName, GameMode& selectedMode) {
    const std::string windowName = "Main Menu";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    m_menuframeWidth = 800;
    m_menuframeHeight = 600;

    cv::Mat menu(m_menuframeHeight, m_menuframeWidth, CV_8UC3); // Canvas for menu

    std::string nameInput, errorMsg = "";
    int selectedIndex = 0;
    std::vector<std::string> gameModes = {"Dodge Balls", "Catch Squares"};

    bool typingName = true;
    bool confirmed = false;
    bool showCursor = true;
    int frameCount = 0;

    std::vector<cv::Rect> modeButtons;

    // Mouse operations
    struct MouseState {
        int x = -1, y = -1;
        bool clicked = false;
        bool doubleClicked = false;
    } mouse;

    cv::setMouseCallback(windowName, [](int event, int x, int y, int, void*userdata) {
        auto* m = reinterpret_cast<MouseState*>(userdata); // TODO: explain Reinterpret_cast
        if (event == cv::EVENT_LBUTTONDOWN) {
            m->x = x;
            m->y = y;
            m->clicked = true;
        }
    }, &mouse);

    while (!confirmed) {
        menu.setTo(cv::Scalar(30, 30, 30)); // Clear the frame every iteration
        frameCount++;

        // Cursor toggle every 15 frames
        if (frameCount % 15 == 0) {
            showCursor = !showCursor;
        }

        // Game title
        cv::putText(menu, "HEAD REACTION GAME", cv::Point(100, 50), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 2);

        // Name input (with blinking cursor "|")
        std::string cursor = (showCursor && typingName) ? "|" : "";
        cv::putText(menu, "Name: " + nameInput + cursor, cv::Point(100, 120), cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(200,200,255), 2);

        // Show error message, if necessary
        if (!errorMsg.empty()) {
            cv::putText(menu, errorMsg, cv::Point(100, 160), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(0,0,255), 2);
        }

        // Game mode options wiht buttons
        modeButtons.clear();
        for (int i = 0; i < gameModes.size(); ++i) {
            cv::Point textPos(100, 220 + i * 60);
            cv::Size textSize = cv::getTextSize(gameModes[i], cv::FONT_HERSHEY_COMPLEX, 0.8, 2, 0);
            cv::Rect button(textPos.x - 10, textPos.y - textSize.height - 10, textSize.width + 20, textSize.height + 20);

            modeButtons.push_back(button);

            cv::Scalar color = (i == selectedIndex) ? cv::Scalar(0, 255, 0) : cv::Scalar(200, 200, 200);
            cv::rectangle(menu, button, color, 2);

            cv::putText(menu, gameModes[i], textPos, cv::FONT_HERSHEY_COMPLEX, 0.8, color, 2);
        }

        // Instructions on the screen
        if (!typingName) {
            cv::putText(menu, "Press Enter to start", cv::Point(100, 400), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(255,255,255), 1);
        }
        cv::putText(menu, "Use W/S or mouseclick to choose game mode", cv::Point(100, 350), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(255,255,255), 1);

        cv::imshow(windowName, menu);
        int key = cv::waitKey(30);

        // Mouse click handling
        if (!typingName) {
            for (size_t i = 0; i < modeButtons.size(); ++i) {
                if (modeButtons[i].contains(cv::Point(mouse.x, mouse.y))) {
                    selectedIndex = static_cast<int>(i); //TODO: Explain static cast
                }
            }
            mouse.clicked = false;
        }

        // Inout name
        if (typingName) {
            if (key == 13 || key == 10) { // Enter 
                std::string nameTrimmed = nameInput;
                errorMsg = validateName(nameTrimmed);

                if (errorMsg.empty()) {
                    // No error -> proceed to mode selection
                    typingName = false;
                }
            }
            else if (key == 8 || key == 127) { // Backspace
                if (!nameInput.empty()) {
                    nameInput.pop_back();
                }
            }
            else if (key >= 32 && key <= 126) { // All printable characters
                if (nameInput.length() < 30) {
                    nameInput += static_cast<char>(key); // TODO: static_cast erklären
                }
            }
        }
        // Select game mode
        else {
            // Navigating game mode
            if (key == 'w') { // up
                selectedIndex = (selectedIndex - 1 + gameModes.size()) % gameModes.size();
            }
            else if (key == 's') { // down
                selectedIndex = (selectedIndex + 1) % gameModes.size();             
            }
            else if (key == 13 || key == 10) { // enter to confirm
                // Visual feedback
                menu.setTo(cv::Scalar(0, 255, 0)); 
                cv::putText(menu, "Starting...", cv::Point(200, 240), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0), 2);
                cv::imshow(windowName, menu);
                cv::waitKey(250); // pause before opening main window
                confirmed = true;
            }
            // Reset mouse state
            mouse.clicked = false;
        }

        // Exit menu with ESC
        if (key == 27) {
            cv::destroyWindow(windowName);
            std::cout << "The game was exited in the menu." << std::endl;
            exit(0); 
        }
    }

    cv::destroyWindow(windowName);
    playerName = nameInput;
    selectedMode = (selectedIndex == 0) ? GameMode::DodgeBalls : GameMode::CatchSquares;

}

// Helperfunction for entering correct name that returns empty string if valid, else returns error message
std::string GUI::validateName(const std::string& name) const {
    if (name.length() < 2 || name.length() > 30) {
        std::cout << "Invalid name length. Name must be between 2 and 30 characters.\n";
        return "Name must be 2-30 characters long.";
    }

    for (char c : name) {
        if (!std::isalpha(c) && c != ' ') {
            std::cout << "Invalid characters. Only letters and spaces allowed.\n";
            return "Only letters and spaces are allowed.";
        }
    }

    return ""; // the entered name is valid
}


// Print the player's name and score
void GUI::printPlayerInfo(const Player& player) const {
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl; // Inhalt evtl. noch überarbeiten
}

// Shows Game Over screen
void GUI::displayGameOver() const {
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "              GAME OVER" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Press ESC to exit..." << std::endl;
}

// Displays final score
void GUI::displayFinalScore(const Player& player) {
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "             Final Results" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Player: " << player.getName() << std::endl;
    std::cout << " Score:  " << player.getScore() << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}
