#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <memory> 
#include "Player.hpp"
#include "FaceDetector.hpp"
#include "GameMode.hpp"
#include "GUI.hpp"

/*
 * @brief Main controller class. 
 Manages player setup, game loop, face detection, GUI update and scoring.
 */
class Game {
public:
    // Constructor with path to Haar cascade 
    Game(const std::string& cascadePath);

    // Default destructor
    ~Game() = default;

    // Start the game (setup, initialization, etc.)
    void startGame();

private:
    // Initializes player (name, mode)
    void setupPlayer();

    // Core game loop (face detection and gameplay)
    void gameLoop();

    // Ends the game (showa final results etc.)
    void endGame();

    // int updateScore(int points); maybe later or GUI/Player

    Player m_player;
    FaceDetector m_faceDetector;
    GUI m_gui;
    GameModeType m_gameMode; // wenn Game Mode implitiert ist, current game mode (1 or 2)
    std::unique_ptr<GameMode> m_gameModePtr; 

    bool m_gameRunning; // Controls game loop


    void spawnObjects(); //
    void updateObjects(cv::Mat& frame, const std::vector<cv::Rect>& faces); //

    // evtl. löschen da schon in GUI und FaceDetector
    /*cv::VideoCapture cap;
    cv::CascadeClassifier faceCascade;
    const std::string windowName = "Face Detection";*/

    std::vector<std::shared_ptr<GameObject>> objects; //
   /* int frameWidth;
    int frameHeight; */

    int spawnTimer = 0; //
    int mode = 1; //- // Default Mode 1, kannst per Konsole setzen
};

#endif // GAME_HPP

