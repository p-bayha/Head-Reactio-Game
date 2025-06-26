cmake_minimum_required(VERSION 3.11)
project(FaceDetectionStarter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Define source and header directions
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)

# Define source files
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/FaceDetector.cpp
    ${SRC_DIR}/Player.cpp
)

# Create executable
add_executable(FaceDetectionStarter ${SOURCES})

# Add include directories
target_include_directories(FaceDetectionStarter PRIVATE ${INC_DIR})

# Link OpenCV libraries
target_link_libraries(FaceDetectionStarter PRIVATE ${OpenCV_LIBS})

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")