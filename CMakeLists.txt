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

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)

add_executable(FaceDetectionTests 
    tests/test_player.cpp
    src/Player.cpp
    tests/test_faceDetector.cpp
    src/FaceDetector.cpp
    tests/test_game.cpp
    #src/game.cpp
    tests/test_GUI.cpp
    src/GUI.cpp
    )

# Includes and linking for test executable
target_include_directories(FaceDetectionTests
    PRIVATE ${INC_DIR} ${TEST_DIR}
)
target_link_libraries(FaceDetectionTests
    PRIVATE GTest::gtest_main ${OpenCV_LIBS}
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(FaceDetectionTests)

message(STATUS "Ensure 'haarcascade_frontalface_default.xml' is in the build/executable directory or update path in main.cpp.")