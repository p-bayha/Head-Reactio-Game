# Head-Reactio-Game
## Project Overview
This project is called Head Ratio Game. It uses OpenCV for face detection and is written in C++.
The current implementation builds a face detection starter program.

## **How to build and run**
### _**Prerequisites**_
- CMake (tested with version 3.x)
- Visual Studio (tested with VS 2019, using vc16)
- OpenCV installed and built (with path set in OpenCV_DIR)

## **Build instructions**
1) Prepare build directory
   - (optional: Remove-Item -Recurse -Force .\build
             mkdir build)
   - cd build
2) Configure with CMake
   Make sure to adapt OpenCV_DIR to your local installation path:
   - cmake .. -A x64 -DOpenCV_DIR="C:\opencv\build\x64\vc16\lib"
3) Build the project: 
   - cmake --build .
4) Run the program:
    - Option 1: Direct:
       - .\Debug\FaceDetectionStarter.exe
    - Option 2 (if binaries and XML not yet copied):
       - Copy-Item "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" -Destination ".\Debug"
        - Copy-Item "C:\opencv\build\x64\vc16\bin\*.dll" -Destination ".\Debug"
        - cd Debug
        - .\FaceDetectionStarter.exe
6) Optional: Clean up build files
    - cd ..
    - Remove-Item -Recurse -Force .\build

## **NOTES:**
- Ensure your PowerShell has permissions to execute scripts and manage processes.
- Adjust OpenCV_DIR and file paths to your local OpenCV installation.
- Tested on Windows 10 x64 with Visual Studio 2019 and OpenCV 4.x.
