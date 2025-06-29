#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


Game::Game(const std::string& cascadePath) : frameWidth(0), frameHeight(0) {
    faceCascade.load(cascadePath);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); //
}

Game::~Game() {
    if (cap.isOpened()) {
        cap.release();}
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

//
void Game::spawnObjects() {
    if (spawnTimer++ >= 20) {
        spawnTimer = 0;

        int size = 20 + (std::rand() % 31);
        float speed = 5.0f + static_cast<float>(std::rand() % 50) / 10.0f;
        Position pos{ std::rand() % frameWidth, 0 };

        if (mode == 1) {
            // Mode 1: nur Kreise in rot, blau, grün
            cv::Scalar color;
            int randColor = std::rand() % 3;
            if (randColor == 0) color = cv::Scalar(0, 0, 255); // Rot
            else if (randColor == 1) color = cv::Scalar(255, 0, 0); // Blau
            else color = cv::Scalar(0, 255, 0); // Grün
            objects.push_back(std::make_shared<Circle>(color, Size{ size, size }, Speed{ speed }, pos));
        } else if (mode == 2) {
            // Mode 2: rote Kreise (dodge), grüne Rechtecke (catch)
            int objType = std::rand() % 2; // 0 = Kreis, 1 = Rechteck

            if (objType == 0) {
                // roter Kreis
                cv::Scalar red = cv::Scalar(0, 0, 255);
                objects.push_back(std::make_shared<Circle>(red, Size{ size, size }, Speed{ speed }, pos));
            } else {
                // grünes Rechteck
                cv::Scalar green = cv::Scalar(0, 255, 0);
                objects.push_back(std::make_shared<Square>(green, Size{ size, size }, Speed{ speed }, pos));
            }
        }
    }
}


void Game::updateObjects(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    spawnObjects();

    for (auto it = objects.begin(); it != objects.end();) {
        auto& obj = *it;
        obj->move();

        bool collisionDetected = false;
        for (const auto& face : faces) {
            if (obj->checkCollision(face)) {
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected) {
            cv::putText(frame, "COLLISION!", cv::Point(30, 30),
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        obj->draw(frame);

        if (obj->getPosition().y > frameHeight) {
            it = objects.erase(it);
        } else {
            ++it;
        }
    }
}
//

void Game::run() {
    std::cout << "Select mode (1 = Dodge the balls, 2 = Catch the squares): ";
    std::cin >> mode;
    if (!initialize()) return;

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        updateObjects(frame, faces);

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow(windowName, frame);
        int key = cv::waitKey(10);
        if (key == 27) break; // ESC
    }
}
