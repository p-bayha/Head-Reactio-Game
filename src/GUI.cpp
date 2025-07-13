#include "GUI.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "Game.hpp"

// Display the welcome menu
void GUI::displayMenu() const {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Welcome to the Head Reaction Game " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    // TODO: Weiterer Inhalt des Menu wie Erklärung und co.
} 

/*void GUI::drawHUD(cv::Mat& frame, const Player& player) {
    std::string info = "Score: " + std::to_string(player.getScore());
    cv::putText(frame, info, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);
} */ // Shows score while playing, add later maybe

void GUI::handleMouseInput(bool& clicked, int x, int y, const std::vector<cv::Rect>& modeButtons) {
    if (clicked && !m_menuState.typingName) {
        for (size_t i = 0; i < modeButtons.size(); ++i) {
            if (modeButtons[i].contains(cv::Point(x, y))) {
                m_menuState.selectedIndex = static_cast<int>(i); //TODO: Explain static cast
                break;
            }
        }
        clicked = false;
    }
}

void GUI::handleKeyboardInput(int key) {
    auto& state = m_menuState;

    // Inout name
    if (state.typingName) {
        if (key == ENTER_KEY || key == 10) { // Enter 
            state.errorMsg = validateName(state.nameInput);

            if (state.errorMsg.empty()) {
                // No error -> proceed to mode selection
                state.typingName = false;
            }
        }
        else if ((key == BACKSPACE_KEY || key == 127) && !state.nameInput.empty()) { // Backspace
                state.nameInput.pop_back();
        }
        else if (key >= 32 && key <= 126 && state.nameInput.length() < 30) { // All printable characters
                state.nameInput += static_cast<char>(key); // TODO: static_cast erklären
        }
    }
    
    // object count input
    else if (state.focusOnObjectCount) {
        if (key == ENTER_KEY || key == 10) {
            try {
                state.n_objects = std::stoi(state.objectCountInput);
                if (state.n_objects <= 0) throw std::invalid_argument("Must be positive");
                state.confirmed = true;
            } catch (...) {
                state.errorMsg = "Enter a positive number.";
                state.objectCountInput.clear();
            }
        }
        else if ((key == BACKSPACE_KEY || key == 127) && !state.objectCountInput.empty()) {
            state.objectCountInput.pop_back();
        }
        else if (key >= '0' && key <= '9' && state.objectCountInput.size() < 3) {
            state.objectCountInput += static_cast<char>(key);
        }
        else if (key == 'a') { // Back to choosing game mode
            state.focusOnObjectCount = false;
        }
    } 
                    
    // Select game mode
    else {
        // Navigating game mode
        const int numModes = 2; // total game modes
        if (key == 'w') { // up
            state.selectedIndex = (state.selectedIndex - 1 + numModes) % numModes; 
        }
        else if (key == 's') { // down
            state.selectedIndex = (state.selectedIndex + 1) % numModes;             
        }
        else if (key == 'd' && state.selectedIndex == 1) {
            state.focusOnObjectCount = true;
            state.objectCountInput.clear();
            state.errorMsg.clear();
        }
        else if ((key == ENTER_KEY || key == 10) &&state. selectedIndex == 0) { // enter to confirm
            state.confirmed = true;
        }
    }
    
}

void GUI::showMainMenuWindow(std::string& playerName, GameModeType& selectedMode, int& n_objects) {
    const std::string windowName = "Main Menu";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(windowName, m_posX, m_posY);

    cv::Mat menu(m_menuframeHeight, m_menuframeWidth, CV_8UC3); // Canvas for menu

    std::vector<std::string> gameModes = {"Dodge Balls", "Catch Squares"};
    std::vector<cv::Rect> modeButtons;

    // Mouse operations
    struct MouseState {
        int x = -1, y = -1;
        bool clicked = false;
    } mouse;

    cv::setMouseCallback(windowName, [](int event, int x, int y, int, void* userdata) {
        MouseState* m = reinterpret_cast<MouseState*>(userdata); // TODO: explain Reinterpret_cast
        if (event == cv::EVENT_LBUTTONDOWN) {
            m->x = x;
            m->y = y;
            m->clicked = true;
        }
    }, &mouse);

    m_menuState = MenuConstants{}; // Reset state at the start

    while (!m_menuState.confirmed) {
        menu.setTo(BG_COLOR); // Clear the frame every iteration
        m_menuState.frameCount++;

        // Cursor toggle every 15 frames
        if (m_menuState.frameCount % 15 == 0) {
            m_menuState.showCursor = !m_menuState.showCursor;
        }

        // Game title
        std::string title = "HEAD REACTION GAME";
        cv::Size titleSize = cv::getTextSize(title, cv::FONT_HERSHEY_COMPLEX, 1.5, 2, &m_baseline);
        cv::putText(menu, title, {m_centerX - titleSize.width / 2, 80}, cv::FONT_HERSHEY_COMPLEX, 1.5, TEXT_COLOR, 2);

        // Name input (with blinking cursor "|")
        std::string cursor = (m_menuState.showCursor && m_menuState.typingName) ? "|" : "";
        std::string nameText = "Name: " + m_menuState.nameInput;
        cv::Size nameSize = cv::getTextSize(nameText, cv::FONT_HERSHEY_COMPLEX, 1.0, 2, &m_baseline); 
        cv::Point nameOrg(m_centerX - nameSize.width / 2, 160);
        cv::putText(menu, nameText, {m_centerX - nameSize.width / 2, 160}, cv::FONT_HERSHEY_COMPLEX, 1.0, {200,200,255}, 2); // TODO: define color

        // Draw the cursor
        if (m_menuState.showCursor && m_menuState.typingName) {
            int cursorX = nameOrg.x + nameSize.width + 2;
            int cursorY = nameOrg.y + nameSize.height;
            cv::putText(menu, "|", {cursorX, nameOrg.y}, cv::FONT_HERSHEY_COMPLEX, 1.0, {200,200,255}, 2); // TODO: color
        }

        // Show error message, if necessary
        if (!m_menuState.errorMsg.empty()) {
            cv::Size errorSize = cv::getTextSize(m_menuState.errorMsg, cv::FONT_HERSHEY_COMPLEX, 0.8, 2, &m_baseline);
            cv::putText(menu, m_menuState.errorMsg, {m_centerX - errorSize.width / 2, 200}, cv::FONT_HERSHEY_COMPLEX, 0.8, ERROR_COLOR, 2);
        }

        // Game mode options with buttons
        modeButtons.clear();
        for (int i = 0; i < gameModes.size(); ++i) {
            cv::Size modeSize = cv::getTextSize(gameModes[i], cv::FONT_HERSHEY_COMPLEX, 1.0, 2, &m_baseline);
            cv::Point textPos(m_centerX - modeSize.width / 2, 270 + i * 80);
            cv::Rect button(textPos.x - 20, textPos.y - modeSize.height - 20, modeSize.width + 40, modeSize.height + 40);

            modeButtons.push_back(button);

            cv::Scalar color = (i == m_menuState.selectedIndex) ? ACTIVE_COLOR : cv::Scalar(200, 200, 200); // TODO: color define in constants
            cv::rectangle(menu, button, color, 2);
            cv::putText(menu, gameModes[i], textPos, cv::FONT_HERSHEY_COMPLEX, 1.0, color, 2);
        }

        // Object count field
        if (!m_menuState.typingName && m_menuState.selectedIndex == 1) {
            std::string countText = "Number of objects: " + m_menuState.objectCountInput + ((m_menuState.focusOnObjectCount && m_menuState.showCursor) ? "|" : "");
            const cv::Rect& selectedButton = modeButtons[1];
            int padding = 20;

            cv::Size countSize = cv::getTextSize(countText, cv::FONT_HERSHEY_COMPLEX, 0.9, 2, &m_baseline);
            cv::Point countPosition(selectedButton.x + selectedButton.width + padding, selectedButton.y + selectedButton.height / 2 + countSize.height / 2);
            cv::putText(menu, countText, countPosition, cv::FONT_HERSHEY_COMPLEX, 0.9, cv::Scalar(255,255,180), 2); // TODO: Color as constant
        }

        // Instructions on the screen
        if (!m_menuState.typingName) {
            std::string helpInstruction = "Use W/S or mouse to select game mode. Press A/S to switch to enter number of objects.";
            cv::Size helpInstructionSize = cv::getTextSize(helpInstruction, cv::FONT_HERSHEY_COMPLEX, 0.6, 1, &m_baseline);
            cv::putText(menu, helpInstruction, {m_centerX - helpInstructionSize.width / 2, m_menuframeHeight - 80}, cv::FONT_HERSHEY_COMPLEX, 0.6, TEXT_COLOR, 1);

            std::string instruction = "Press Enter to start";
            cv::Size instructionSize = cv::getTextSize(instruction, cv::FONT_HERSHEY_COMPLEX, 0.7, 1, &m_baseline);
            cv::putText(menu, instruction, {m_centerX - instructionSize.width / 2, m_menuframeHeight -40}, cv::FONT_HERSHEY_COMPLEX, 0.7, TEXT_COLOR, 1);
        }
        cv::imshow(windowName, menu);
        int key = cv::waitKey(30);

        handleMouseInput(mouse.clicked, mouse.x, mouse.y, modeButtons);
        handleKeyboardInput(key);                   

            if (m_menuState.confirmed) {
                // Visual feedback
                menu.setTo(cv::Scalar(0, 255, 0)); // TODO: color
                std::string startMessage = "Starting...";
                cv::Size textSize = cv::getTextSize(startMessage, cv::FONT_HERSHEY_COMPLEX, 1.0, 2, &m_baseline);
                int centerX = m_menuframeWidth / 2 - textSize.width / 2;
                int centerY = m_menuframeHeight / 2 - textSize.height / 2;
                cv::putText(menu, startMessage, {centerX, centerY}, cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0, 0, 0), 2); //TODO: color
                cv::imshow(windowName, menu);
                cv::waitKey(250); // pause before opening main window
                break;
            }

            // Reset mouse state
            mouse.clicked = false;

        // Exit menu with ESC
        if (key == ESC_KEY) {
            cv::destroyWindow(windowName);
            std::cout << "The game was exited in the menu." << std::endl;
            exit(0); 
        }
    }

    cv::destroyWindow(windowName);

    // Set outputs
    playerName = m_menuState.nameInput;
    selectedMode = (m_menuState.selectedIndex == 0) ? GameModeType::DodgeBalls : GameModeType::CatchSquares;
    n_objects = m_menuState.n_objects;

}

// Helper function for entering correct name that returns empty string if valid, else returns error message
std::string GUI::validateName(const std::string& name) const {

    // Trim leading spaces to clear up name
    size_t start = name.find_first_not_of(' ');
    if (start == std::string::npos) {
        std::cout << "Invalid name length. Name must be between 2 and 30 characters.\n";
        return "Name must be 2-30 characters long.";        
    }
    
    // Trim tailing spaces
    size_t end = name.find_last_not_of(' ');
    std::string trimmed = name.substr(start, end - start + 1); // new trimmed string

    if (trimmed.length() < 2 || trimmed.length() > 30) {
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

std::string GUI::getModeString(GameModeType mode) const {
    // Auch Teil der Game mode klasse, nachher evtl. anders umgesetzt
    std::string modeString;
    switch (mode) {
        case GameModeType::DodgeBalls: 
            modeString = "Dodge Balls";
            break;
        case GameModeType::CatchSquares: 
            modeString = "Catch Squares";
            break;
        // evtl. nachher noch weitere modes
        default: 
            modeString = "Unknown";
            break;

    }
    return modeString;
}

// Print the player's name and score
void GUI::printPlayerInfo(const Player& player, GameModeType mode, int n_objects) const {
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl; // Inhalt evtl. noch überarbeiten
    std::cout << "\nStarting game in mode " << getModeString(mode) << "...\n" << std::endl;
    if (getModeString(mode) == "Catch Squares") {
    std::cout << "      with " << n_objects << " objects...\n" << std::endl;
    }
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
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}
