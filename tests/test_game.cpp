#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "Game.hpp"

// Test the constructor (no throwing exceptions)
TEST(GameTest, ConstructorDoesNotThrow) {
    EXPECT_NO_THROW(Game game("haarcascade_frontalface_default.xml"));
}

// Test calling startGame() without throwing
TEST(GameTest, StartGameDoesNotThrow) {
    Game game("haarcascade_frontalface_default.xml");
    game.enableTestMode();
    EXPECT_NO_THROW(game.startGame());
} 

// Test startGame() being called twice in a row safely
TEST(GameTest, StartGameCallingTwiceNoCrash) {
    Game game("haarcascade_frontalface_default.xml");
    game.enableTestMode();
    EXPECT_NO_THROW(game.startGame());
    EXPECT_NO_THROW(game.startGame());
} 

// Test if the player name is correctly set in test mode.
TEST(GameTest, PlayerName_IsTestPlayer_InTestMode) {
    Game game("haarcascade_frontalface_default.xml");
    game.enableTestMode();
    game.startGame();
    EXPECT_EQ(game.getPlayerName(), "TestPlayer");
}

// Test that the game is no linger running after startGame() complites
TEST(GameTest, GameStopsRunning_AfterStartGame) {
    Game game("haarcascade_frontalface_default.xml");
    game.enableTestMode();
    game.startGame();
    EXPECT_FALSE(game.isGameRunning());
}

// Test destructor (no throwing)
TEST(GameTest, DestructorDoesNotThrow) {
    EXPECT_NO_THROW(Game game("haarcascade_frontalface_default.xml"));
} 

