cmake_minimum_required(VERSION 3.17)
project(FaceDetectionStarter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV directories
 include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(FaceDetectionStarter
    src/main.cpp
    src/Game.cpp
    #src/GameObject.cpp
    src/Circle.cpp
    src/Square.cpp
)

# Include inc directories
target_include_directories(FaceDetectionStarter PRIVATE ${CMAKE_SOURCE_DIR}/inc)


target_link_libraries(FaceDetectionStarter
    ${OpenCV_LIBS}
)

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")