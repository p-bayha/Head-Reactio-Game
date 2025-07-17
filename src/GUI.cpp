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
    std::cout << " HOW TO USE THE MENU:" << std::endl;
    std::cout << " 1. Enter your name using your keyboard, then press ENTER." << std::endl;
    std::cout << " 2. Use W and S to move between game modes." << std::endl;
    std::cout << " 3. For 'Catch Squares': Press D to enter the number of objects." << std::endl;
    std::cout << "    Press A to cancel object input." << std::endl;
    std::cout << " 4. Press ENTER again to confirm and start the game." << std::endl;
    std::cout << " 5. Press ESC anytime to quit." << std::endl;
    std::cout << "-----------------------------------" << std::endl;
} 

// Handles mouse input for selecting game mode buttons
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

// Handles keyboard input for navigating the menu and entering name/objact count
void GUI::handleKeyboardInput(int key) {
    auto& state = m_menuState;

    if (state.typingName) {
        if (key == ENTER_KEY || key == ENTER_KEYTWO) { 
            state.errorMsg = validateName(state.nameInput);

            if (state.errorMsg.empty()) {
                state.typingName = false;
            }
        }
        else if ((key == BACKSPACE_KEY || key == BACKSPACE_KEYTWO) && !state.nameInput.empty()) {
                state.nameInput.pop_back();
        }
        else if (key >= FIRST_ALPHABETICAL_KEY && key <= LAST_ALPHABETICAL_KEY && state.nameInput.length() < MAX_NAME_LENGTH) { // All printable characters
                state.nameInput += static_cast<char>(key); 
        }
        return;
    }
    
    if (state.focusOnObjectCount) {
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
        else if (key == 'a') { 
            state.focusOnObjectCount = false;
        }
        return;
    }      

    // Navigate game modes
    const int numModes = 2;
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
    

// Drawing functions for HUD during gameplay
void GUI::drawGameMode(cv::Mat& frame, std::string currentGameMode) {
    cv::putText(frame, currentGameMode, {HUD_MARGIN_X, HUD_MARGIN_Y}, HUD_FONT, HUD_FONT_SCALE, TEXT_COLOR, HUD_FONT_THICKNESS); 
}

void GUI::drawScore(cv::Mat& frame, int score) const {
    std::string scoreText = "Score: " + std::to_string(score);
    cv::putText(frame, scoreText, {HUD_MARGIN_X, HUD_MARGIN_Y + HUD_LINE_SPACING}, HUD_FONT, HUD_FONT_SCALE, TEXT_COLOR, HUD_FONT_THICKNESS); 
}

void GUI::drawGameOver(cv::Mat& frame, const Player& player) {
    cv::Scalar whiteColor(255, 255, 255);
    cv::Scalar redColor(0, 0, 255);

    // GAME OVER Text 
    int gameOverFont = cv::FONT_HERSHEY_TRIPLEX;
    std::string gameOverText = "GAME OVER";
    cv::Size textSize = cv::getTextSize(gameOverText, gameOverFont, 2.5, 5, &m_baseline);
    cv::Point center((frame.cols - textSize.width) / 2, (frame.rows + textSize.height) / 2 - 50);
    cv::putText(frame, gameOverText, center, gameOverFont, 2.5, redColor, 5);

    // Name text
    std::string nameText = "Name: " + player.getName();
    cv::Size nameSize = cv::getTextSize(nameText, HUD_FONT, 1.0, 2, &m_baseline);
    cv::Point namePos((frame.cols - nameSize.width) / 2, center.y + 70);
    cv::putText(frame, nameText, namePos, HUD_FONT, 1.0, whiteColor, 2);

    // Score text
    std::string scoreText = "Score: " + std::to_string(player.getScore());
    cv::Size scoreSize = cv::getTextSize(scoreText, HUD_FONT, 1.0, 2, &m_baseline);
    cv::Point scorePos((frame.cols - scoreSize.width) / 2, namePos.y + 40);
    cv::putText(frame, scoreText, scorePos, HUD_FONT, 1.0, whiteColor, 2);
}

void GUI::showMainMenuWindow(std::string& playerName, GameModeType& selectedMode, int& n_objects) {
    const std::string windowName = "Main Menu";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(windowName, m_posX, m_posY);

    cv::Mat menuFrame(m_menuframeHeight, m_menuframeWidth, CV_8UC3); 

    std::vector<std::string> gameModes = {"Dodge Balls", "Catch Squares"};
    std::vector<cv::Rect> modeButtons;

    struct MouseState {
        int x = -1, y = -1;
        bool clicked = false;
    } mouse;

    cv::setMouseCallback(windowName, [](int event, int x, int y, int, void* userdata) {
        MouseState* m = reinterpret_cast<MouseState*>(userdata); 
        if (event == cv::EVENT_LBUTTONDOWN) {
            m->x = x;
            m->y = y;
            m->clicked = true;
        }
    }, &mouse);

    m_menuState = MenuConstants{}; 

    while (!m_menuState.confirmed) {
        menuFrame.setTo(BG_COLOR); 
        m_menuState.frameCount++;

        // Cursor toggle every 15 frames
        if (m_menuState.frameCount % 15 == 0) {
            m_menuState.showCursor = !m_menuState.showCursor;
        }

        drawTitle(menuFrame);
        drawNameInput(menuFrame);
        drawGameModeButtons(menuFrame, gameModes, modeButtons);
        drawErrorMessage(menuFrame, gameModes, modeButtons);
        drawInstructions(menuFrame);

        cv::imshow(windowName, menuFrame);
        int key = cv::waitKey(30);

        handleMouseInput(mouse.clicked, mouse.x, mouse.y, modeButtons);
        handleKeyboardInput(key);

        if (m_menuState.confirmed) {
            menuFrame.setTo(MENU_COLOR); 
            std::string startMessage = "Starting...";
            cv::Size textSize = cv::getTextSize(startMessage, MENU_FONT, START_FONT_SCALE, START_THICKNESS, &m_baseline);
            int centerX = m_menuframeWidth / 2 - textSize.width / 2;
            int centerY = m_menuframeHeight / 2 - textSize.height / 2;
            cv::putText(menuFrame, startMessage, {centerX, centerY}, MENU_FONT, START_FONT_SCALE, START_TEXT_COLOR); 
            cv::imshow(windowName, menuFrame);
            cv::waitKey(START_MESSAGE_DELAY_MS); // 250ms
            break;
        }
        mouse.clicked = false;

        if (key == ESC_KEY) {
            cv::destroyWindow(windowName);
            std::cout << "The game was exited in the menu." << std::endl;
            exit(0);
        }
    }

    cv::destroyWindow(windowName);
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

    if (m_menuState.showCursor && m_menuState.typingName) {
        int cursorX = nameOrg.x + nameSize.width + 2;
        int cursorY = nameOrg.y + nameSize.height;
        cv::putText(menu, "|", {cursorX, nameOrg.y}, MENU_FONT, CURSOR_FONT_SCALE, CURSOR_COLOR, CURSOR_THICKNESS); 
    }

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
        std::string helpInstruction = "Use W/S or mouse to select game mode | Press D to set objects | Press A to go back to selection mode";
        cv::Size helpInstructionSize = cv::getTextSize(helpInstruction, MENU_FONT, HELP_FONT_SCALE, HELP_THICKNESS, &m_baseline);
        cv::putText(menu, helpInstruction, {m_centerX - helpInstructionSize.width / 2, m_menuframeHeight - 80}, MENU_FONT, HELP_FONT_SCALE, TEXT_COLOR, HELP_THICKNESS);

        std::string instruction = "Press Enter to start";
        cv::Size instructionSize = cv::getTextSize(instruction, MENU_FONT, INSTRUCTION_FONT_SCALE, INSTRUCTION_THICKNESS, &m_baseline);
        cv::putText(menu, instruction, {m_centerX - instructionSize.width / 2, m_menuframeHeight - 40}, MENU_FONT, INSTRUCTION_FONT_SCALE, TEXT_COLOR, INSTRUCTION_THICKNESS);
    }
}

std::string GUI::validateName(const std::string& name) const {
    size_t start = name.find_first_not_of(' ');
    if (start == std::string::npos) {
        std::cout << "Invalid name length. Name must be between 2 and 30 characters.\n";
        return "Name must be 2-30 characters long.";        
    }
    
    size_t end = name.find_last_not_of(' ');
    std::string trimmed = name.substr(start, end - start + 1); 

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

    return ""; 
}

std::string GUI::getModeString(GameModeType mode) const {
    std::string modeString;
    switch (mode) {
        case GameModeType::DodgeBalls: 
            modeString = "Dodge Balls";
            break;
        case GameModeType::CatchSquares: 
            modeString = "Catch Squares";
            break;
        default: 
            modeString = "Unknown";
            break;

    }
    return modeString;
}

void GUI::printPlayerInfo(const Player& player, GameModeType mode, int n_objects) const {
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl; // Inhalt evtl. noch überarbeiten
    std::cout << "\nStarting game in mode " << getModeString(mode) << "...\n" << std::endl;
    if (getModeString(mode) == "Catch Squares") {
    std::cout << "      with " << n_objects << " objects...\n" << std::endl;
    }
}

void GUI::displayGameOver() const {
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "              GAME OVER" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Press ESC to exit..." << std::endl;
}

void GUI::displayFinalScore(const Player& player) {
    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "             Final Results" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}
