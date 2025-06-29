#ifndef GAME_HPP
#define GAME_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <vector> //
#include <memory> //

#include "Circle.hpp" //
#include "Square.hpp" //
#include "GameObject.hpp" //
#include "Utils.hpp" //

class Game {
public:
    Game(const std::string& cascadePath);
    ~Game();
    bool initialize();
    void run();
private:
    void spawnObjects(); //
    void updateObjects(cv::Mat& frame, const std::vector<cv::Rect>& faces); //

    cv::VideoCapture cap;
    cv::CascadeClassifier faceCascade;
    const std::string windowName = "Face Detection";

    std::vector<std::shared_ptr<GameObject>> objects; //
    int frameWidth;
    int frameHeight;
    int spawnTimer = 0; //
    int mode = 1; //- // Default Mode 1, kannst per Konsole setzen
};

#endif // GAME_HPP
