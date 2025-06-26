#include "FaceDetector.hpp"
#include "Player.hpp"
#include <string>

int main() {
    // Create a Player and get the name
    Player player;
    player.inputName();

    // Print player info to confirm input 
    ///@brief later also choose game mode and display information about game
    player.printPlayerInfo();

    // Path to the Haar cascade XML file for face detection
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

    // Create FaceDetector instance for face detection
    FaceDetector faceDetector(cascadeFilePath);

    if (!faceDetector.initialize()) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1; 
    }

    // Run main detection loop
    faceDetector.detectFace();

    return 0;
}