cmake_minimum_required(VERSION 3.17)
project(FaceDetectionStarter)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Define source, header and tests directions
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Define source files
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/FaceDetector.cpp
    ${SRC_DIR}/Player.cpp
    ${SRC_DIR}/GUI.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Circle.cpp
    ${SRC_DIR}/Square.cpp
    ${SRC_DIR}/DodgeBallsMode.cpp
    ${SRC_DIR}/CatchSquaresMode.cpp
)

# Create executable
add_executable(FaceDetectionStarter ${SOURCES})


# Add include directories
target_include_directories(FaceDetectionStarter PRIVATE ${INC_DIR})

# Link OpenCV libraries
target_link_libraries(FaceDetectionStarter PRIVATE ${OpenCV_LIBS})

# GoogleTest integration
include(FetchContent)

FetchContent_Declare(
    googletest
    ULR https://github.com/google/googletest/archive/release-1.14.0.zip
)

# Prevent gtest from overriding main()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailavle(googletest)

enable_testing()

# Test sources
file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)

# Test executable
add_executable(UnitTests ${TEST_SOURCE})

# INclude same headers
target_include_directiories(UnitTests PRIVATE ${INC_DIR})

# Link against source files and gtest
target_link_libraries(UnitTests PRIVATE
    gtest_main
    ${OpenCV_LIBS}
) 

target_sources(UnitTests PRIVATE
    ${SRC_DIR}/FaceDetector.cpp
    ${SRC_DIR}/Player.cpp
    ${SRC_DIR}/GUI.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Circle.cpp
    ${SRC_DIR}/Square.cpp
    ${SRC_DIR}/DodgeBallsMode.cpp
    ${SRC_DIR}/CatchSquaresMode.cpp
)

# Register Tests
include(GoogleTest)
gtest_discover_tests(UnitTests)


message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")