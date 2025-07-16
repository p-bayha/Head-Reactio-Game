#include <gtest/gtest.h>
#include "DodgeBallsMode.hpp"
#include "Player.hpp"
#include "GUI.hpp"

TEST(DodgeBallsModeTest, InitializesWithoutCrashing) {
    Player player;
    GUI gui;
    DodgeBallsMode mode(player, gui, 480, 640);

    EXPECT_NO_THROW(mode.initialize());
}
