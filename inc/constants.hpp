#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <opencv2/opencv.hpp>
#include "GameMode.hpp"

// Struct for menu-related states

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

// Key codes
static constexpr int ENTER_KEY = 13;
static constexpr int ENTER_KEYTWO = 10;
static constexpr int ESC_KEY = 27;
static constexpr int BACKSPACE_KEY = 8;
static constexpr int BACKSPACE_KEYTWO = 127;
static constexpr int FIRST_ALPHABETICAL_KEY = 32;
static constexpr int LAST_ALPHABETICAL_KEY = 126;

// Input limits
static constexpr int MAX_NAME_LENGTH = 30;
static constexpr int MAX_OBJECT_COUNT_DIGITS = 3;

// Fonts
static constexpr int HUD_FONT = cv::FONT_HERSHEY_SIMPLEX;
static constexpr int MENU_FONT = cv::FONT_HERSHEY_COMPLEX;

// HUD layout and styling
static constexpr int HUD_MARGIN_X = 10;
static constexpr int HUD_MARGIN_Y = 30;
static constexpr int HUD_LINE_SPACING = 40;

static constexpr int HUD_FONT_SCALE = 1.0;
static constexpr int HUD_FONT_THICKNESS = 2;

// Menu layout, Y positions
static constexpr int TITLE_Y = 80;
static constexpr int NAME_Y = 160;
static constexpr int ERROR_Y = 200;
static constexpr int GAME_MODE_START_Y = 270;
static constexpr int GAME_MODE_VERTICAL_SPACING = 80;
static constexpr int MENU_PADDING = 20;

// Menu font scales
static constexpr double TITLE_FONT_SCALE = 1.5;
static constexpr double NAME_FONT_SCALE = 1.0;
static constexpr double CURSOR_FONT_SCALE = 1.0;
static constexpr double ERROR_FONT_SCALE = 0.8;
static constexpr double GAME_MODE_FONT_SCALE = 1.0;
static constexpr double COUNT_FONT_SCALE = 0.9;
static constexpr double HELP_FONT_SCALE = 0.6;
static constexpr double INSTRUCTION_FONT_SCALE = 0.7;
static constexpr double START_FONT_SCALE = 1.0;

// Menu text thickness
static constexpr int TITLE_THICKNESS = 2;
static constexpr int NAME_THICKNESS = 2;
static constexpr int CURSOR_THICKNESS = 2;
static constexpr int ERROR_THICKNESS = 2;
static constexpr int GAME_MODE_THICKNESS = 2;
static constexpr int COUNT_THICKNESS = 2;
static constexpr int HELP_THICKNESS = 1;
static constexpr int INSTRUCTION_THICKNESS = 1;
static constexpr int START_THICKNESS= 2;

// Timings 
static constexpr int START_MESSAGE_DELAY_MS = 250;

// Default fallback resolution for faceDetector
static constexpr int DEFAULT_CAMERA_WIDTH = 1200;
static constexpr int DEFAULT_CAMERA_HEIGHT = 1000;

// Face detection parameters
static constexpr double FACE_DETECTION_SCALE_FACTOR = 1.1;
static constexpr int FACE_DETECTION_MIN_NEIGHBORS = 3;
static constexpr int FACE_DETECTION_FLAGS = 0;
static constexpr int FACE_DETECTION_MIN_SIZE = 60;

// Face drawing parameters
static constexpr int FACE_RECTANGLE_THICKNESS = 2;
static constexpr int DEFAULT_FACE_RECTANGLE_WIDTH = 100;
static constexpr int DEFAULT_FACE_RECTANGLE_HEIGHT = 100;

// Colors 
const cv::Scalar BG_COLOR = cv::Scalar(30, 30, 30); // dark gray
const cv::Scalar TEXT_COLOR = cv::Scalar(255, 255, 255); // white
const cv::Scalar ACTIVE_COLOR = cv::Scalar(0, 255, 0); // green
const cv::Scalar ERROR_COLOR = cv::Scalar(0, 0, 255); // red
const cv::Scalar CURSOR_COLOR = cv::Scalar(200, 200, 255); // light blue
const cv::Scalar COUNT_COLOR = cv::Scalar(255, 255, 180); // yellow-tinted white
const cv::Scalar BUTTON_INACTIVE_COLOR = cv::Scalar(200, 200, 200); // gray
const cv::Scalar MENU_COLOR = cv::Scalar(200, 255, 200); // pale green
const cv::Scalar START_TEXT_COLOR = cv::Scalar(0, 0, 0); // black on light background
const cv::Scalar FACE_RECTANGLE_COLOR = cv::Scalar(0, 255, 0); // green

#endif // CONSTANTS_HPP