#include "FaceDetector.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include <string>

int main() {
    GUI gui; // Interface handler
    Player player; // Game player instance

    // Show menu and input player name
    gui.displayMenu();
    player.setName(gui.inputName());

    // Choose game mode (future: part of game mode class maybe)
    int gameMode = gui.askGameMode();

    // Show player information
    gui.printPlayerInfo(player);

    // Path to the Haar cascade XML file for face detection
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

    // Create FaceDetector instance for face detection
    FaceDetector faceDetector(cascadeFilePath);

    if (!faceDetector.initialize()) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1; 
    }

    if (!faceDetector.isInitialized()) {
        std::cerr << "Detector not ready." << std::endl;
        return 1;
    }

    // Start game
    std::cout << "\nStarting game in mode " << gameMode << "...\n" << std::endl;

    // Display camera/game window
    gui.displayGameWindow(faceDetector);

    // End game
    gui.displayGameOver();
    gui.displayFinalScore(player);

    return 0;
}