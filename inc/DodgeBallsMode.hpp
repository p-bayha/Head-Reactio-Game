#ifndef DODGEBALLSMODE_HPP
#define DODGEBALLSMODE_HPP

#include "GameMode.hpp"
#include "Circle.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>

class DodgeBallsMode : public GameMode {
public:
    DodgeBallsMode(Player& player, int frameWidth, int frameHeight); // <- muss exakt so drin stehen
    void initialize() override;
    bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) override;
    int getScore() const override;

private:
    Player& m_player;
    int m_frameWidth;
    int m_frameHeight;
    int m_spawnTimer;
    std::vector<std::shared_ptr<Circle>> m_circles;
};

#endif
