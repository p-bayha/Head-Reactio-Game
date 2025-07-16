#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief Handles face detection using OpenCV's Haar cascade classifier,
 * Loads the classifier, initializes the camera, captures frames, defects faces,
 * and draws rectangles around detected faces.
 */
class FaceDetector {
public:
    // Constructor: Load the Haar cascade for face detection from the given file path.
    FaceDetector(const std::string& cascadePath);

    // Destructor: Release all resources (camera and windows).
    ~FaceDetector();

    /**
     * @brief Initialises the camera, window and verifies resources. 
     * @return True if initialization was successful, false otherwise.
    */
    bool initialize();

    // Checks if the FaceDetector has been successfully initialized.
    bool isInitialized() const;

    /**
     * @brief Captures and processes one frame, draws rectangles on detected faces.
     * @return Processed frame with face rectangles drawn.
     */
    cv::Mat getProcessedFrame();
    std::vector<cv::Rect> detectFaces(const cv::Mat& frame);

    // Needed for testing
    friend class FaceDetectorTest_ReturnsDefaultFaceRectWhenNoDetection_Test;
    friend class FaceDetectorTest_ReturnsPreviousFaceOnDetectionFailure_Test;
    friend class FaceDetectorTest_DetectFacesInImage_Test;
    friend class FaceDetectorTest_DetectMultibleFacesInImage_Test;
    friend class FaceDetectorTest_NoFaceImageTriggersDefaultRect_Test;


private:
    // Releases camera and destroys any OpenCV windows created.
    void releaseResources();

    cv::VideoCapture cap; // Video capture device.
    cv::CascadeClassifier faceCascade; // Haar cascade classifier for face detection.
    const std::string m_windowName = "Face Detection"; // Name of the display window.

    std::vector<cv::Rect> m_lastDetectedFaces; // Stores the last result

    // Returns a default face rectangle in the center of the frame
    cv::Rect getDefaultFaceRect(const cv::Mat& frame) const;

    int m_frameWidth; // Width of the camera frame
    int m_frameHeight; // Height of the camera frame

    bool m_initialized = false;
};

#endif // FACEDETECTOR_HPP