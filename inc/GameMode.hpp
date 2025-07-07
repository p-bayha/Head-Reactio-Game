#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <opencv2/opencv.hpp>
#include "Player.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>

class GameMode {
public:
    virtual ~GameMode() {}
    virtual void initialize() = 0;
    virtual bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) = 0;
    virtual int getScore() const = 0;
};

#endif //GAMEMODE_HPP

