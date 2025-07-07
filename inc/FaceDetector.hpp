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
    bool isInitialized() const;

    /**
     * @brief Captures and processes one frame, draws rectangles on detected faces.
     * @return Processed frame with face rectangles drawn.
     */
    cv::Mat getProcessedFrame();
    std::vector<cv::Rect> detectFaces(const cv::Mat& frame);

private:
    // Releases camera and destroys OpenCV windows
    void releaseResources();

    cv::VideoCapture cap; // Video capture object
    cv::CascadeClassifier faceCascade; // Detect face in the frame
    const std::string m_windowName = "Face Detection"; // Window name for display

    int m_frameWidth; // Width of the camera frame
    int m_frameHeight; // Height of the camera frame

    bool m_initialized;
};

#endif // FACEDETECTOR_HPP