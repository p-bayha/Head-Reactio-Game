#include <gtest/gtest.h>
#include "Player.hpp"

// Test defalt constructor
TEST(PlayerTest, DefaultScoreIsZero) {
    Player p;
    EXPECT_EQ(p.getScore(), 0);
}

// Test setting and getting name
TEST(PlayerTest, SetAndGetName) {
    Player p;
    p.setName("Name");
    EXPECT_EQ(p.getName(), "Name");
}

// Test changing score with positive value
TEST(PlayerTest, ChangeScorePositive) {
    Player p;
    p.changeScore(10);
    EXPECT_EQ(p.getScore(), 10);
}

// Test changing score with negative value
TEST(PlayerTest, ChangeScoreNegative) {
    Player p;
    p.changeScore(10);
    p.changeScore(-5);
    EXPECT_EQ(p.getScore(), 5);
}

// Test changing score into negative value
TEST(PlayerTest, ChangeScoreIntoNegative) {
    Player p;
    p.changeScore(-10);
    EXPECT_EQ(p.getScore(), 0);
}

// Test setting score directly
TEST(PlayerTest, SetScorePositive) {
    Player p;
    p.setScore(42);
    EXPECT_EQ(p.getScore(), 42);
}

// Test setting score with negative value should reset to zero
TEST(PlayerTest, SetScoreNegativeResetsToZero) {
    Player p;
    p.setScore(-10);
    EXPECT_EQ(p.getScore(), 0);
}