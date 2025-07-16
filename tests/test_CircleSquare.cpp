#include <gtest/gtest.h>
#include "Circle.hpp"
#include "Square.hpp"
#include "Utils.hpp"
#include <opencv2/opencv.hpp>

TEST(CircleTest, CheckCollision_InsideFace_ReturnsTrue) {
    Circle c(cv::Scalar(0, 0, 255), {30, 30}, {0.0f}, {100, 100});
    cv::Rect face(105, 105, 50, 50); // Mitte vom Kreis liegt in diesem Face
    EXPECT_TRUE(c.checkCollision(face));
}

TEST(CircleTest, CheckCollision_OutsideFace_ReturnsFalse) {
    Circle c(cv::Scalar(0, 0, 255), {30, 30}, {0.0f}, {10, 10});
    cv::Rect face(200, 200, 50, 50);
    EXPECT_FALSE(c.checkCollision(face));
}

TEST(SquareTest, CheckCollision_OverlapWithFace_ReturnsTrue) {
    Square s(cv::Scalar(0, 255, 0), {40, 40}, {0.0f}, {100, 100});
    cv::Rect face(110, 110, 30, 30); // überschneidet sich
    EXPECT_TRUE(s.checkCollision(face));
}

TEST(SquareTest, CheckCollision_NoOverlapWithFace_ReturnsFalse) {
    Square s(cv::Scalar(0, 255, 0), {40, 40}, {0.0f}, {10, 10});
    cv::Rect face(300, 300, 50, 50); // weit weg
    EXPECT_FALSE(s.checkCollision(face));
}