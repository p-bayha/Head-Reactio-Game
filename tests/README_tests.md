# Unit Tests – FaceDetectionStarter (C++ OpenCV)

This guide explains how to build and run the unit tests for the `FaceDetectionStarter` project using CMake and GoogleTest.

---

## Prerequisites

- CMake 3.17+
- A C++17 compiler (e.g., MSVC, g++)
- OpenCV installed and accessible in your system
- GoogleTest is automatically fetched by CMake
- The file `haarcascade_frontalface_default.xml` must be available for the FaceDetector test to work (see below)

---

## Build & Run the Tests

If you are using Windows PowerShell, here is the **exact working sequence**:


### Step 1 – Clean old build files
```powershell
Remove-Item -Recurse -Force build
mkdir build
cd build
```

### Step 2 – Configure CMake (in Debug mode)
```powershell
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

### Step 3 – Compile the project including tests
```powershell
cmake --build .
```

## Run the Tests
Once build completes:
### Step 4 – Find the test executable
```powershell
Get-ChildItem -Recurse -Filter FaceDetectionTests.exe
```

### Step 5 – Run the test executable
```powershell
& .\Debug\FaceDetectionTests.exe
```

## Known Issue: FaceDetector Test Fails
If the test `FaceDetectorTest.InitializeWithValideCascade` fails, it is usually because the XML file is missing:
```powershell
Error: Could not load Haar cascade file from haarcascade_frontalface_default.xml
```
### Fix
Between Step 4 and Step 5 do as follows:

Copy the `haarcascade_frontalface_default.xml` file to the directory where your test executable is located (usually `build/Debug/`):
```powershell
Copy-Item "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" `
  -Destination "C:\yourproject_path\build\Debug"
```
Alternatively, you can hardcode the full path in your test file temporarily.

## Test Files Included
- test_player.cpp
- test_GUI.cpp
- test_faceDetector.cpp
- test_CatchSquaresMode.cpp
- test_CircleSquare.cpp
- test_DodgeBallsMode.cpp

## Notes
> Make sure to rebuild (`cmake --build .`) after adding new test files.
> If you use Visual Studio, make sure your test project is set as the startup project.
> The FaceDetector test accesses the webcam — make sure it’s available, or skip that test.
