#ifndef CATCHSQUARESMODE_HPP
#define CATCHSQUARESMODE_HPP

#include "GameMode.hpp"
#include "Circle.hpp"
#include "Square.hpp"

class CatchSquaresMode : public GameMode {
public:
    CatchSquaresMode(Player& player, int frameWidth, int frameHeight, int totalObjects);
    void initialize() override;
    bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) override;
    int getScore() const override;

private:
    Player& m_player;
    int m_frameWidth;
    int m_frameHeight;
    int m_spawnTimer;
    int m_remainingObjects;
    std::vector<std::shared_ptr<GameObject>> m_objects;
};

#endif
