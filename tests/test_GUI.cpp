#include <gtest/gtest.h>
#include "GUI.hpp"

// Reject empty string or strings containing only spaces.
TEST(GUITest, ValidateNameRejectsEmpty) {
    GUI gui;
    EXPECT_EQ(gui.validateName(""), "Name must be 2-30 characters long.");
    EXPECT_EQ(gui.validateName("   "), "Name must be 2-30 characters long.");
}

// Reject names longer than the maximum allowed length.
TEST(GUITest, ValidateNameTooLong) {
    GUI gui;
    std::string longName(50, 'a');
    EXPECT_EQ(gui.validateName(longName), "Name must be 2-30 characters long.");
}

// Reject invalid characters (symbols, digits, non-ASCII).
TEST(GUITest, ValidateNameWithInvalidCharacters) {
    GUI gui;
    EXPECT_EQ(gui.validateName("%&$"), "Only letters and spaces are allowed.");
    EXPECT_EQ(gui.validateName("120"), "Only letters and spaces are allowed.");
    EXPECT_EQ(gui.validateName("Ann&a"), "Only letters and spaces are allowed.");
    EXPECT_EQ(gui.validateName("Björn"), "Only letters and spaces are allowed.");
}

// Accept valid names with letters.
TEST(GUITest, ValidateNameValid) {
    GUI gui;
    EXPECT_EQ(gui.validateName("Knut"), "");
}

// Accept names with leading/tailing spaces after trimming.
TEST(GUITest, ValidateNameTrimsSpaces) {
    GUI gui;
    EXPECT_EQ(gui.validateName("  Knut  "), ""); 
}

// Accept names with spaces between words.
TEST(GUITest, ValidateNameAcceptsSpacesInside) {
    GUI gui;
    EXPECT_EQ(gui.validateName("Max Mustermann"), "");
}

// Boundary condition: accept exactly 2 characters and exactly 30 characters.
TEST(GUITest, ValidateNameBoundaryLengths) {
    GUI gui;
    EXPECT_EQ(gui.validateName("Al"), ""); 
    EXPECT_EQ(gui.validateName(std::string(30, 'a')), ""); 
}


