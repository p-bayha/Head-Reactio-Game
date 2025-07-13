#include <gtest/gtest.h>
#include "FaceDetector.hpp"

const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

TEST(FaceDetectorTest, InitializeWithValideCascade) {
    FaceDetector faceDetector(cascadeFilePath);
    EXPECT_FALSE(faceDetector.isInitialized());
    EXPECT_TRUE(faceDetector.initialize());
    EXPECT_TRUE(faceDetector.isInitialized());
}

TEST(FaceDetectorTest, InitializeWithInvalidCascade) {
    FaceDetector faceDetector("invalid_cascade_path.xml");
    EXPECT_FALSE(faceDetector.isInitialized());
    EXPECT_FALSE(faceDetector.initialize());
    EXPECT_FALSE(faceDetector.isInitialized());
}

// still need images to test this function

TEST(FaceDetectorTest, DetectFacesInImage) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());
}

