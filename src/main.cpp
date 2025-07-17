#include "FaceDetector.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include <string>

int main() {
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

    Game game(cascadeFilePath);
    game.startGame();

    return 0;
}