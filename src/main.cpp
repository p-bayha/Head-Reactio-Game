#include "FaceDetector.hpp"
#include <string>

int main() {
    // Path to the Haar cascade XML file for face detection
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";

    // Create FaceDetector instance for face detection
    FaceDetector faceDetector(cascadeFilePath);

    if (!faceDetector.initialize()) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1; 
    }

    // Run main detection loop
    faceDetector.detectFace();

    return 0;
}