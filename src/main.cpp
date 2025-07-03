#include "FaceDetector.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include <string>

int main() {
    // Path to the Haar cascade XML file for face detection
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    
    Game game(cascadeFilePath);
    game.startGame();

    //GUI gui; // Interface handler
    //Player player; // Game player instance

    return 0;
}