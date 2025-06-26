#include "FaceDetector.hpp"
#include <string>

int main() {
    std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}