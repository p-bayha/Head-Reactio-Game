#include "GUI.hpp"
#include "Player.hpp"
#include "FaceDetector.hpp"

// Display the welcome menu
void GUI::displayMenu() const {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " Welcome to the Head Reaction Game " << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    // TO DO: Weiterer Inhalt des Menu wie Erklärung und co.
}


// Prompts the user to input their name via terminal
std::string GUI::inputName() {
    std::string name;
    while (true) {
        std::cout << "Please enter your name: ";
        std::getline(std::cin, name); //Gets the full name, not just one word

        // Check length
        if (name.length() < 2 || name.length() > 30) {
            std::cout << "Invalid length. Name must be between 2 and 30 characters.\n";
            continue;
        }

        // Check if only alphabetic characters or spaces are used
        bool valid = true;
        for (char c : name) {
            if (!std::isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid characters. Only letters and spaces allowed.\n";
            continue;
        }

        return name;
    }
}

// Print the player's name and score
void GUI::printPlayerInfo(const Player& player) const {
    std::cout << "Player: " << player.getName() << " | Score: " << player.getScore() << std::endl; // Inhalt evtl. noch überarbeiten
}

// Asks the player for the game mode
GameMode GUI::askGameMode() const {
    int mode = 0;
    std::cout << "Select Game Mode:\n";
    std::cout << "1. Dodge Balls\n";
    std::cout << "2. Catch Squares\n";
    // Maybe 3. Mixed?
    std::cout << "Your choice (1 or 2): ";

    while (true) {
        std::cin >> mode;

        if (std::cin.fail() || (mode != 1 && mode != 2)) {
            std::cin.clear(); // clear error-flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush input
            std::cout << "Invalid input. Please enter 1 or 2: ";
        } 
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush remaining
            return static_cast<GameMode>(mode); // TODO: static_cast erklären
        } 
    }
}

// Ab jetzt in game
/*void GUI::displayGameWindow(FaceDetector& detector) {
    const std::string windowName = "Face Detection";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    while(true) {
        cv::Mat frame = detector.getProcessedFrame();

    if (frame.empty()) {
        std::cerr << "Error: FaceDetection not properly initialized." << std::endl;
        return;
    }

    // Display the frame
    cv::imshow(windowName, frame);

    // Exit loop if ESC key (ASCII 27) is pressed 
    int key = cv::waitKey(10);
    if (key == 27) {
        break; 
    }
    }

    cv::destroyWindow(windowName); 
} */

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
