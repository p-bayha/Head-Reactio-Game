#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "FaceDetector.hpp"

const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

// Helper: Create an empty black image 
cv::Mat createEmptyImage(int width = 640, int height = 480) {
    return cv::Mat::zeros(height, width, CV_8UC3);
}

std::string getImagePath(const std::string& fileName) {
    std::filesystem::path currentFile = __FILE__;
    std::filesystem::path baseDir = currentFile.parent_path(); // Path to the test file
    std::filesystem::path fullPath = baseDir / "test_image" / fileName;
    return fullPath.string();
}


// Test initialization with valid Haar cascade file
TEST(FaceDetectorTest, InitializeWithValidCascade) {
    FaceDetector faceDetector(cascadeFilePath);
    EXPECT_FALSE(faceDetector.isInitialized());
    EXPECT_TRUE(faceDetector.initialize());
    EXPECT_TRUE(faceDetector.isInitialized());
}

// Test initialization with invalid Haar cascade file path.
TEST(FaceDetectorTest, InitializeWithInvalidCascade) {
    FaceDetector faceDetector("invalid_cascade_path.xml");
    EXPECT_FALSE(faceDetector.isInitialized());
    EXPECT_FALSE(faceDetector.initialize());
    EXPECT_FALSE(faceDetector.isInitialized());
}

// Test returns default face rectangle when no faces detected and no previous cache
TEST(FaceDetectorTest, ReturnsDefaultFaceRectWhenNoDetection) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());

    cv::Mat emptyFrame = createEmptyImage();
    auto faces = faceDetector.detectFaces(emptyFrame);

    ASSERT_EQ(faces.size(), 1);

    cv::Rect defaultRect = faceDetector.getDefaultFaceRect(emptyFrame);
    EXPECT_EQ(faces[0], defaultRect);
}

// Test returns previous detection when current detection fails
TEST(FaceDetectorTest, ReturnsPreviousFaceOnDetectionFailure) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());

    // Simulate previous detection
    cv::Rect simulatedFace(20, 20, 80, 80);
    faceDetector.m_lastDetectedFaces = {simulatedFace};

    // Provide empty image to force no detection
    cv::Mat emptyFrame = createEmptyImage();
    auto faces = faceDetector.detectFaces(emptyFrame);

    ASSERT_EQ(faces.size(), 1);
    EXPECT_EQ(faces[0], simulatedFace);
}

// Test face detection on an actual face image
TEST(FaceDetectorTest, DetectFacesInImage) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());

    // image with a face
    cv::Mat faceImage = cv::imread(getImagePath("face.jpeg"));
    ASSERT_FALSE(faceImage.empty()) << "missing test_image/face.jpeg";

    auto faces = faceDetector.detectFaces(faceImage);

    ASSERT_GT(faces.size(), 0);
    EXPECT_EQ(faces.size(), faceDetector.m_lastDetectedFaces.size());
}

// Test multiple face detection on an actual face image
TEST(FaceDetectorTest, DetectMultipleFacesInImage) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());

    // image with a face
    cv::Mat multiFaceImage = cv::imread(getImagePath("multiple_face.jpeg"));
    ASSERT_FALSE(multiFaceImage.empty()) << "missing test_image/multiple_faces.jpeg";

    auto faces = faceDetector.detectFaces(multiFaceImage);

    ASSERT_GE(faces.size(), 2); // two faces
}

// Test no face image -> fallback to default
TEST(FaceDetectorTest, NoFaceImageTriggersDefaultRect) {
    FaceDetector faceDetector(cascadeFilePath);
    ASSERT_TRUE(faceDetector.initialize());

    cv::Mat noFaceImage = cv::imread(getImagePath("no_face.jpeg"));
    ASSERT_FALSE(noFaceImage.empty()) << "missing test_image/no_faces.jpeg";

    auto faces = faceDetector.detectFaces(noFaceImage);

    ASSERT_EQ(faces.size(), 1); 
    EXPECT_EQ(faces[0], faceDetector.getDefaultFaceRect(noFaceImage));

    EXPECT_EQ(faceDetector.m_lastDetectedFaces.size(), 1);
    EXPECT_EQ(faceDetector.m_lastDetectedFaces[0], faceDetector.getDefaultFaceRect(noFaceImage));

}

