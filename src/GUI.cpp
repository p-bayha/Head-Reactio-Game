#include "GUI.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "Game.hpp"
#include "constants.hpp"

// Display the welcome menu
void GUI::displayMenu() const {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Welcome to the Head Reaction Game " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    // TODO: Weiterer Inhalt des Menu wie Erklärung und co.
} 

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
        if (key == ENTER_KEY || key == ENTER_KEYTWO) { 
            state.errorMsg = validateName(state.nameInput);

            if (state.errorMsg.empty()) {
                // No error -> proceed to mode selection
                state.typingName = false;
            }
        }
        else if ((key == BACKSPACE_KEY || key == BACKSPACE_KEYTWO) && !state.nameInput.empty()) {
                state.nameInput.pop_back();
        }
        else if (key >= FIRST_ALPHABETICAL_KEY && key <= LAST_ALPHABETICAL_KEY && state.nameInput.length() < MAX_NAME_LENGTH) { // All printable characters
                state.nameInput += static_cast<char>(key); 
        }
    }
    
    // object count input
    else if (state.focusOnObjectCount) {
        if (key == ENTER_KEY || key == ENTER_KEYTWO) {
            try {
                state.n_objects = std::stoi(state.objectCountInput);
                if (state.n_objects <= 0) throw std::invalid_argument("Must be positive");
                state.confirmed = true;
            } catch (...) {
                state.errorMsg = "Enter a positive number.";
                state.objectCountInput.clear();
            }
        }
        else if ((key == BACKSPACE_KEY || key == BACKSPACE_KEYTWO) && !state.objectCountInput.empty()) {
            state.objectCountInput.pop_back();
        }
        else if (key >= '0' && key <= '9' && state.objectCountInput.size() < MAX_OBJECT_COUNT_DIGITS) {
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
        else if ((key == ENTER_KEY || key == ENTER_KEYTWO) &&state. selectedIndex == 0) { // enter to confirm
            state.confirmed = true;
        }
    }
    
}

void GUI::drawGameMode(cv::Mat& frame, std::string currentGameMode) {
    cv::putText(frame, currentGameMode, {HUD_MARGIN_X, HUD_MARGIN_Y}, HUD_FONT, HUD_FONT_SCALE, TEXT_COLOR, HUD_FONT_THICKNESS); 
}

void GUI::drawScore(cv::Mat& frame, int score) const {
    std::string scoreText = "Score: " + std::to_string(score);
    cv::putText(frame, scoreText, {HUD_MARGIN_X, HUD_MARGIN_Y + HUD_LINE_SPACING}, HUD_FONT, HUD_FONT_SCALE, TEXT_COLOR, HUD_FONT_THICKNESS); 
}

void GUI::drawGameOver(cv::Mat& frame) {
    std::string GameOverText = "GAME OVER";
    cv::Size GameOverTextSize = cv::getTextSize(GameOverText, HUD_FONT, 2.0, 3, &m_baseline);
    cv::Point center((frame.cols - GameOverTextSize.width) / 2, (frame.rows + GameOverTextSize.height) / 2);
    cv::putText(frame, GameOverText, center, HUD_FONT, 2.0, ERROR_COLOR, 3); 
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

        drawTitle(menu);
        drawNameInput(menu);
        drawGameModeButtons(menu, gameModes, modeButtons);
        drawErrorMessage(menu, gameModes, modeButtons);
        drawInstructions(menu);


        cv::imshow(windowName, menu);
        int key = cv::waitKey(30);

        handleMouseInput(mouse.clicked, mouse.x, mouse.y, modeButtons);
        handleKeyboardInput(key);

            if (m_menuState.confirmed) {
                // Visual feedback
                menu.setTo(MENU_COLOR); 
                std::string startMessage = "Starting...";
                cv::Size textSize = cv::getTextSize(startMessage, MENU_FONT, START_FONT_SCALE, START_THICKNESS, &m_baseline);
                int centerX = m_menuframeWidth / 2 - textSize.width / 2;
                int centerY = m_menuframeHeight / 2 - textSize.height / 2;
                cv::putText(menu, startMessage, {centerX, centerY}, MENU_FONT, START_FONT_SCALE, START_TEXT_COLOR); 
                // Show this message and wait briefly before continuing
                cv::imshow(windowName, menu);
                cv::waitKey(START_MESSAGE_DELAY_MS); // 250ms
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

void GUI::drawTitle(cv::Mat& menu) {
    std::string title = "HEAD REACTION GAME";
    cv::Size titleSize = cv::getTextSize(title, MENU_FONT, TITLE_FONT_SCALE, TITLE_THICKNESS, &m_baseline);
    cv::putText(menu, title, {m_centerX - titleSize.width / 2, TITLE_Y}, MENU_FONT, TITLE_FONT_SCALE, TEXT_COLOR, TITLE_THICKNESS);
}

void GUI::drawNameInput(cv::Mat& menu) {
    std::string cursor = (m_menuState.showCursor && m_menuState.typingName) ? "|" : "";
    std::string nameText = "Name: " + m_menuState.nameInput;
    cv::Size nameSize = cv::getTextSize(nameText, MENU_FONT, NAME_FONT_SCALE, NAME_THICKNESS, &m_baseline); 
    cv::Point nameOrg(m_centerX - nameSize.width / 2, NAME_Y);
    cv::putText(menu, nameText, {nameOrg.x, NAME_Y}, MENU_FONT, NAME_FONT_SCALE, CURSOR_COLOR, NAME_THICKNESS); 

    // Draw the cursor
    if (m_menuState.showCursor && m_menuState.typingName) {
        int cursorX = nameOrg.x + nameSize.width + 2;
        int cursorY = nameOrg.y + nameSize.height;
        cv::putText(menu, "|", {cursorX, nameOrg.y}, MENU_FONT, CURSOR_FONT_SCALE, CURSOR_COLOR, CURSOR_THICKNESS); 
    }

    // Show error message, if necessary
    if (!m_menuState.errorMsg.empty()) {
        cv::Size errorSize = cv::getTextSize(m_menuState.errorMsg, MENU_FONT, ERROR_FONT_SCALE, ERROR_THICKNESS, &m_baseline);
        cv::Point errorOrg(m_centerX - errorSize.width / 2, ERROR_Y);
        cv::putText(menu, m_menuState.errorMsg, {errorOrg.x, ERROR_Y}, MENU_FONT, ERROR_FONT_SCALE, ERROR_COLOR, ERROR_THICKNESS);
    }
}

void GUI::drawGameModeButtons(cv::Mat& menu, std::vector<std::string> gameModes, std::vector<cv::Rect>& modeButtons) {
    modeButtons.clear();
    for (int i = 0; i < gameModes.size(); ++i) {
        cv::Size modeSize = cv::getTextSize(gameModes[i],MENU_FONT , GAME_MODE_FONT_SCALE, GAME_MODE_THICKNESS, &m_baseline);
        int yPos = GAME_MODE_START_Y + i * GAME_MODE_VERTICAL_SPACING;
        cv::Point textPos(m_centerX - modeSize.width / 2, yPos);
        cv::Rect button(textPos.x - MENU_PADDING, textPos.y - modeSize.height - MENU_PADDING, modeSize.width + 2 * MENU_PADDING, modeSize.height + 2 * MENU_PADDING);

        modeButtons.push_back(button);

        cv::Scalar color = (i == m_menuState.selectedIndex) ? ACTIVE_COLOR : BUTTON_INACTIVE_COLOR; 
        cv::rectangle(menu, button, color, 2);
        cv::putText(menu, gameModes[i], textPos, MENU_FONT, GAME_MODE_FONT_SCALE, color, GAME_MODE_THICKNESS);
    }
}

void GUI::drawErrorMessage(cv::Mat& menu, std::vector<std::string> gameModes, std::vector<cv::Rect>& modeButtons) {
    if (!m_menuState.typingName && m_menuState.selectedIndex == 1) {
        std::string countText = "Number of objects: " + m_menuState.objectCountInput + ((m_menuState.focusOnObjectCount && m_menuState.showCursor) ? "|" : "");
        const cv::Rect& selectedButton = modeButtons[1];

        cv::Size countSize = cv::getTextSize(countText, MENU_FONT, COUNT_FONT_SCALE, COUNT_THICKNESS, &m_baseline);
        cv::Point countPosition(selectedButton.x + selectedButton.width + MENU_PADDING, selectedButton.y + selectedButton.height / 2 + countSize.height / 2);
        cv::putText(menu, countText, countPosition, MENU_FONT, COUNT_FONT_SCALE, COUNT_COLOR, COUNT_THICKNESS); 
    }
}

void GUI::drawInstructions(cv::Mat&menu) {
    if (!m_menuState.typingName) { 
        std::string helpInstruction = "Use W/S or mouse to select game mode. Press A/S to switch to enter number of objects.";
        cv::Size helpInstructionSize = cv::getTextSize(helpInstruction, MENU_FONT, HELP_FONT_SCALE, HELP_THICKNESS, &m_baseline);
        cv::putText(menu, helpInstruction, {m_centerX - helpInstructionSize.width / 2, m_menuframeHeight - 80}, MENU_FONT, HELP_FONT_SCALE, TEXT_COLOR, HELP_THICKNESS);

        std::string instruction = "Press Enter to start";
        cv::Size instructionSize = cv::getTextSize(instruction, MENU_FONT, INSTRUCTION_FONT_SCALE, INSTRUCTION_THICKNESS, &m_baseline);
        cv::putText(menu, instruction, {m_centerX - instructionSize.width / 2, m_menuframeHeight - 40}, MENU_FONT, INSTRUCTION_FONT_SCALE, TEXT_COLOR, INSTRUCTION_THICKNESS);
    }
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
