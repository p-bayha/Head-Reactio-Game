#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <opencv2/opencv.hpp>
#include "Player.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>

enum class GameModeType {
    None, 
    DodgeBalls, 
    CatchSquares 
};

class GameMode {
public:
    virtual ~GameMode() = default;
    // Initializes the game mode, resetting any necessary state
    virtual void initialize() = 0;
    // Updates the game state, processes collisions, and draws the frame
    virtual bool update(cv::Mat& frame, const std::vector<cv::Rect>& faces) = 0;
    // Returns the current score for the game mode
    virtual int getScore() const = 0;
};

#endif //GAMEMODE_HPP

