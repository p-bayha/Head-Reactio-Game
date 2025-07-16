#include "FaceDetector.hpp"
#include "constants.hpp"

#include <iostream>

// Constructor: Load Haar cascade classifier from given file path.
FaceDetector::FaceDetector(const std::string& cascadePath) : m_frameWidth(0), m_frameHeight(0), m_initialized(false) {
    if (!faceCascade.load(cascadePath)) {
        std::cerr << "[Error] Failed to load Haar cascade file from: " << cascadePath << std::endl;
    }
}

// Destructor: Release resources cleanly
FaceDetector::~FaceDetector() {
    releaseResources();
}

// Initialise camera and check all resources; set default resolution if needed
bool FaceDetector::initialize() {
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "[Error] Could not open camera." << std::endl;
        return false;
    }

    m_frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    m_frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Set default resolution if invalid
    if (m_frameWidth <= 0 || m_frameHeight <= 0) {
        m_frameWidth = 1200;
        m_frameHeight = 1000;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, m_frameWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_frameHeight);
    }

    if (faceCascade.empty()) {
        std::cerr << "[Error] Haar cascade is not loaded." << std::endl;
        return false;
    }

    m_initialized = true;
    return true;
}

// Check if initialization was successful
bool FaceDetector::isInitialized() const {
    return m_initialized;
}

// Capture a frame, detect faces and annotate frame with rectangles
cv::Mat FaceDetector::getProcessedFrame() {
    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
        std::cerr << "[Warning] Empty frame captured, stopping." << std::endl;
        return {};
    }

    // Mirror frame horizontally for natural webcam view
    cv::flip(frame, frame, 1);

    // Detect face in the frame
    std::vector<cv::Rect> faces = detectFaces(frame);

    // Draw rectangles around detected faces
    for (const auto& face : faces) {
        cv::rectangle(frame, face, FACE_RECTANGLE_COLOR, FACE_RECTANGLE_THICKNESS);
    } 

    return frame;
}

// Releases resources (camera and window)
void FaceDetector::releaseResources() {
    if (cap.isOpened()) {
        cap.release();
    }
    cv::destroyAllWindows();
    m_initialized = false; 
}

// Detect faes in a provided frame and return bounding rectangles
std::vector<cv::Rect> FaceDetector::detectFaces(const cv::Mat& frame) {
    std::vector <cv::Rect> faces;
    faceCascade.detectMultiScale(frame, faces, FACE_DETECTION_SCALE_FACTOR, FACE_DETECTION_MIN_NEIGHBORS, FACE_DETECTION_FLAGS, cv::Size(FACE_DETECTION_MIN_SIZE, FACE_DETECTION_MIN_SIZE));

    if (!faces.empty()) {
        m_lastDetectedFaces = faces;
        return faces;
    }

    // No face found fallback
    if (!m_lastDetectedFaces.empty()) {
        std::cerr << "[Info] No face detected -> reusing previous detection." << std::endl;
        return m_lastDetectedFaces;
    }

    // If still no data -> return default face
    std::cerr << "[Info] No previous face -> returning default fallback." << std::endl;

    cv::Rect defaultRect = getDefaultFaceRect(frame);
    m_lastDetectedFaces = {defaultRect};
    return m_lastDetectedFaces; 
}

cv::Rect FaceDetector::getDefaultFaceRect(const cv::Mat& frame) const {
    return cv::Rect(
        frame.cols / 2 - DEFAULT_FACE_RECTANGLE_WIDTH / 2, frame.rows / 2 - DEFAULT_FACE_RECTANGLE_HEIGHT / 2, DEFAULT_FACE_RECTANGLE_WIDTH, DEFAULT_FACE_RECTANGLE_WIDTH
    );
}