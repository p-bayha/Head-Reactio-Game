# Head Reaction Game

## Project Overview
This project is called **Head Reaction Game**.  
It uses **OpenCV** for face detection and is written in **C++**.

The current implementation builds a face detection starter program that uses a webcam to detect faces in real-time.  
Additionally, this project explores head proportions (ratios), which are extended into a game tool.

---

## Implementation Details & Extensions
- Implemented in `FaceDetectionStarter.cpp` with modular design for easy extension.
- Uses OpenCV's `haarcascade_frontalface_default.xml` classifier for face detection.
- Managed with **CMake**, builds cleanly on Windows using Visual Studio 2019.
- Includes GoogleTest for basic unit tests.

### Extensions & Special Features
- Adjustable scaling factor for face detection to experiment with sensitivity.
- Prepared structure for ratio calculations (head width to height etc.).
- Ensured compatibility for easy copying of XML classifiers and OpenCV DLLs.

---

## How to build and run

### _Prerequisites_
- **CMake** (tested with version 3.x)
- **Visual Studio** (tested with VS 2019, using `vc16`)
- **OpenCV** installed and built (make sure `OpenCV_DIR` is set correctly)

---

### Build instructions
1) Prepare build directory (optional cleanup):
```powershell
Remove-Item -Recurse -Force .\build
mkdir build
cd build
```

2) Configure with CMake (adapt `OpenCV_DIR` to your local installation path):
```powershell
cmake .. -A x64 -DOpenCV_DIR="C:\opencv\build\x64\vc16\lib"
```
3) Build the project:
```powershell
cmake --build . --config Debug
```
### Run the programm:
#### Option 1
If all files are already in place:
```powershell
.\Debug\FaceDetectionStarter.exe
```
#### Option 2- if `Error: Could not load Haar cascade file.` occurs: 
The program expects the `haarcascade_frontalface_default.xml` to be in the **same directory** as your `.exe` (typically `build\Debug`).

So copy the Haar cascade file and the OpenCV DLLs there:
```powershell
cd Debug
Copy-Item "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" -Destination "."
Copy-Item "C:\opencv\build\x64\vc16\bin\*.dll" -Destination "."
.\FaceDetectionStarter.exe
```

### Notes
> Ensure `haarcascade_frontalface_default.xml` is present in the same directory as your `.exe`.
> Otherwise, you will see:
> ```
> Error: Could not load Haar cascade file.
> Error initializing FaceDetector.
> ```
Tested on **Windows 10 x64** with **Visual Studio 2019** and **OpenCV 4.x.**
Ensure your **PowerShell** has permissions to execute scripts and manage processes.

No responsibility is taken for external libraries (OpenCV).
The program compiles and runs without errors on a Windows PC as long as OpenCV is set up correctly.



