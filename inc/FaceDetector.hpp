#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <string>

// FaceDetector: Handles face detection using OpenCV
class FaceDetector {
public:
    // Constructor: Load the Haar cascade for face detection
    FaceDetector(const std::string& cascadePath);

    // Destructor: Release all resources
    ~FaceDetector();

    // Initialises the camera, window and checks resources
    bool initialize();

    // Main loop: Capture and process frames
    void run();

private:
    // Releases camera and destroys OpenCV windows
    void releaseResources();

    cv::VideoCapture cap; // Video capture object
    cv::CascadeClassifier faceCascade; // Detect face in the frame
    const std::string windowName = "Face Detection"; // Window name for display
    
    int frameWidth; // Width of the camera frame
    int frameHeight; // Height of the camera frame
};

#endif // FACEDETECTOR_HPP