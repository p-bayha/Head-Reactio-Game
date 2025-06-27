#include "FaceDetector.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include <string>

int main() {
    GUI gui;
    Player player;

    // Menu, welcome and enter player name
    gui.displayMenu();
    std::string name = gui.inputName();
    player.setName(name);

    // choose game mode
    int gameMode = gui.askGameMode();

    // show player information
    gui.printPlayerInfo(player);

    // Path to the Haar cascade XML file for face detection
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

    // Create FaceDetector instance for face detection
    FaceDetector faceDetector(cascadeFilePath);
    if (!faceDetector.initialize()) {
        std::cerr << "Initialization failed!" << std::endl;
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