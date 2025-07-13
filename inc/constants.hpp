#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <opencv2/opencv.hpp>
#include "GameMode.hpp"

struct MenuConstants {
    std::string nameInput;
    std::string objectCountInput;
    std::string errorMsg;

    int selectedIndex = 0;
    bool typingName = true;
    bool focusOnObjectCount = false;
    bool confirmed = false;
    bool showCursor = true;
    int frameCount = 0;
    int n_objects = 0;

    GameModeType m_gameMode; 
};

static constexpr int ENTER_KEY = 13;
static constexpr int ESC_KEY = 27;
static constexpr int BACKSPACE_KEY = 8;
static constexpr int MAX_NAME_LENGTH = 30;
static constexpr int MAX_OBJECT_COUNT_DIGITS = 3;

const cv::Scalar BG_COLOR = cv::Scalar(30, 30, 30);
const cv::Scalar TEXT_COLOR = cv::Scalar(255, 255, 255);
const cv::Scalar ACTIVE_COLOR = cv::Scalar(0, 255, 0);
const cv::Scalar ERROR_COLOR = cv::Scalar(0, 0, 255);

#endif // CONSTANTS_HPP