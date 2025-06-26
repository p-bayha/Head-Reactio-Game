#include "FaceDetector.hpp"
#include <iostream>

// Constructor: Load the Haar cascade for face detection
FaceDetector::FaceDetector(const std::string& cascadePath) : m_frameWidth(0), m_frameHeight(0) {
    if (!faceCascade.load(cascadePath)) {
        std::cerr << "Error: COuld not load Haar cascade file from " << cascadePath << std::endl;
    }
}

// Destructor: Release all resources
FaceDetector::~FaceDetector() {
    releaseResources();
}

// Releases resources (camera and window)
void FaceDetector::releaseResources() {
    if (cap.isOpened()) {
        cap.release();
    }
    cv::destroyAllWindows();
}

// Initialises the camera, window and checks resources
bool FaceDetector::initialize() {
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return false;
    }

    m_frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    m_frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // If camera doesn't provide a valid resolution, set to default 
    if (m_frameWidth == 0 || m_frameHeight == 0) {
        m_frameWidth = 640;
        m_frameHeight = 480;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, m_frameWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_frameHeight);
    }

    if (faceCascade.empty()) {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }

    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

// Main loop: Capture and process frames
void FaceDetector::detectFace() {
    if (!cap.isOpened() || faceCascade.empty()) {
        std::cerr << "Error: FaceDetection not properly initialized." << std::endl;
        return;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Warning: Empty frame captured, stopping." << std::endl;
            break;
        }

        // Flip image horizontally for natural webcam view
        cv::flip(frame, frame, 1);

        // Detect face in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        // Draw rectangle around recognized face
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Display the frame
        cv::imshow(m_windowName, frame);

        // Exit loop if ESC key (ASCII 27) is pressed 
        int key = cv::waitKey(10);
        if (key == 27) {
            break; 
        }

    }

    releaseResources();
}