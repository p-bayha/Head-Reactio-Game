#include "Game.hpp"
#include "Player.hpp"
#include "DodgeBallsMode.hpp"
#include "CatchSquaresMode.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

Game::Game(const std::string& cascadePath) : frameWidth(0), frameHeight(0) {
    faceCascade.load(cascadePath);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Game::~Game() {
    if (cap.isOpened()) {
        cap.release();
    }
    cv::destroyAllWindows();
}

bool Game::initialize() {
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return false;
    }
    frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    if (frameWidth == 0 || frameHeight == 0) {
        frameWidth = 640;
        frameHeight = 480;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);
    }

    if (faceCascade.empty()) {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

void Game::run() {
    Player player;
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    player.setName(name);

    std::cout << "Select mode (1 = Dodge the balls, 2 = Catch the squares): ";
    std::cin >> mode;

    if (!initialize()) return;

    std::unique_ptr<GameMode> gameMode;

    if (mode == 1) {
        // Dodge Balls Mode: läuft unendlich, bis man getroffen wird
        gameMode = std::make_unique<DodgeBallsMode>(player, frameWidth, frameHeight);
    } else if (mode == 2) {
        // Catch Squares Mode: spielt N Objekte
        int n;
        std::cout << "Enter number of objects (N): ";
        std::cin >> n;
        gameMode = std::make_unique<CatchSquaresMode>(player, frameWidth, frameHeight, n);
    } else {
        std::cerr << "Invalid mode." << std::endl;
        return;
    }

    gameMode->initialize();

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        if (!gameMode->update(frame, faces)) {
            break; // Game over oder fertig
        }

        cv::imshow(windowName, frame);
        int key = cv::waitKey(10);
        if (key == 27) break; // ESC
    }

    std::cout << "Game Over, " << player.getName()
              << "! Your score: " << player.getScore() << std::endl;
}
