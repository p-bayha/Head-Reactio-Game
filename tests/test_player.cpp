#include <gtest/gtest.h>
#include "Player.hpp"

// Test defalt constructor initializes score to 0
TEST(PlayerTest, DefaultScoreIsZero) {
    Player player;
    EXPECT_EQ(player.getScore(), 0);
}

// Test setting and getting the player's name
TEST(PlayerTest, SetAndGetName) {
    Player player;
    player.setName("Marta");
    EXPECT_EQ(player.getName(), "Marta");
}

// Test empty string as name
TEST(PlayerTest, SetEmptyName) {
    Player player;
    player.setName("");
    EXPECT_EQ(player.getName(), "");
}

// Test increasing score with a positive delta
TEST(PlayerTest, ChangeScorePositive) {
    Player player;
    player.changeScore(10);
    EXPECT_EQ(player.getScore(), 10);
}

// Test changing score with negative delta
TEST(PlayerTest, ChangeScoreNegative) {
    Player player;
    player.changeScore(10);
    player.changeScore(-5);
    EXPECT_EQ(player.getScore(), 5);
}

// Test changing score with zero delta
TEST(PlayerTest, ChangeScoreWithZero) {
    Player player;
    player.setScore(5);
    player.changeScore(0);
    EXPECT_EQ(player.getScore(), 5);
}

// Test that score cannot go below zero using changeScore
TEST(PlayerTest, ChangeScoreIntoNegative) {
    Player player;
    player.changeScore(-10);
    EXPECT_EQ(player.getScore(), 0);
}

// Test direct score assignment with a positive value
TEST(PlayerTest, SetScorePositive) {
    Player player;
    player.setScore(42);
    EXPECT_EQ(player.getScore(), 42);
}

// Test setting a negative score clamps to zero
TEST(PlayerTest, SetScoreNegativeResetsToZero) {
    Player player;
    player.setScore(-10);
    EXPECT_EQ(player.getScore(), 0);
}


