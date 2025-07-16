#ifndef DODGEBALLSMODE_HPP
#define DODGEBALLSMODE_HPP

#include "GameMode.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include <opencv2/opencv.hpp>

class DodgeBallsMode : public GameMode {
public:
    DodgeBallsMode(Player& player, GUI& gui, int height, int width);

    void initialize() override;
    bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) override;
    int getScore() const override;

private:
    Player& m_player;
    GUI& m_gui;
    int m_frameHeight;
    int m_frameWidth;
};

#endif
