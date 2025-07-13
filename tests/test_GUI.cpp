#include <gtest/gtest.h>
#include "GUI.hpp"

TEST(GUITest, ValidateNameRejectsEmpty) {
    GUI gui;
    EXPECT_EQ(gui.validateName(""), "Name must be 2-30 characters long.");
    EXPECT_EQ(gui.validateName("   "), "Name must be 2-30 characters long.");
}

TEST(GUITest, ValidateNameTooLong) {
    GUI gui;
    std::string longName(50, 'a');
    EXPECT_EQ(gui.validateName(longName), "Name must be 2-30 characters long.");
}

TEST(GUITest, ValidateNameWithInvalidCharacters) {
    GUI gui;
    EXPECT_EQ(gui.validateName("%&$"), "Only letters and spaces are allowed.");
    EXPECT_EQ(gui.validateName("120"), "Only letters and spaces are allowed.");
}

TEST(GUITest, ValidateNameValid) {
    GUI gui;
    EXPECT_EQ(gui.validateName("Alice"), "");
}

// more tests with mode but needs fixing first