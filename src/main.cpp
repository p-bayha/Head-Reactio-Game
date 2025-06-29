#include "Game.hpp"
#include <string>

int main() {
    std::string cascadeFilePath = "C:\\Users\\saraz\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}