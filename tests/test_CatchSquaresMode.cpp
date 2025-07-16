#include <gtest/gtest.h>
#include "CatchSquaresMode.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

TEST(CatchSquaresModeTest, Initialize_ResetsScoreAndClearsObjects) {
    Player player;
    GUI gui;
    CatchSquaresMode mode(player, gui, 480, 640, 5);

    player.setScore(10); // vorher ein Score
    mode.initialize();

    EXPECT_EQ(player.getScore(), 0); // Score wurde zurückgesetzt
}

TEST(CatchSquaresModeTest, GameEndsWhenNoObjectsRemaining) {
    Player player;
    GUI gui;
    CatchSquaresMode mode(player, gui, 480, 640, 0); // keine Objekte mehr zu erzeugen
    mode.initialize();

    cv::Mat dummyFrame(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    std::vector<cv::Rect> dummyFaces;

    bool gameContinues = mode.update(dummyFrame, dummyFaces);

    EXPECT_FALSE(gameContinues); // Spiel soll sofort enden
}
