# Head Reaction Game

The **Head Reaction Game** is a C++ application developed as part of the Object-Oriented Programming module at DHBW Stuttgart (2025).  
It combines real-time **face detection** using **OpenCV** with interactive mechanics to create a webcam-based reaction game.

Players control the game by moving their head, which is tracked live using the webcam. Depending on the selected mode, the player must either **dodge** or **catch** falling objects to gain or lose points.

---

## Functional Overview

The application consists of the following components:

- **Face Detection** using OpenCV's Haar Cascade Classifier.
- **Game Mechanics** with two modes:
  - **1) Dodge the Balls**: Avoid falling colored circles. Touching one ends the game.
  - **2) Catch the Squares**: Catch green squares and avoid red circles; score adjusts accordingly.
- **Real-Time Score Display** and **Game Over Feedback (in Mode 1) including the player’s name.
- **Console-Based Menu** to input player name, select game mode, and (in Mode 2) the number of falling objects.
- **Graphical User Interface** based on OpenCV’s `imshow()` with its drawing utilities.
- **Unit Testing** using GoogleTest to validate all major logic components.

---

## Key Features and Extensions

- **Modular OOP Design** with reusable components and clean separation of concerns.
- **Fallback Handling**: If no face is detected, previous detection data is reused.
- **Two Game Modes** with randomized sizes, colors, and speeds.
- **Scoreboard Extension**: Final score and player name are saved to a `.txt` file.
- **Input Validation** with meaningful error feedback.
- **Unit Tests** for collision logic, state transitions, and component correctness.

---

## Implementation Details & Extensions
- Core gameplay in `main.cpp`, with logic delegated to modular classes in `/src` and `/inc`.
- Uses OpenCV's `haarcascade_frontalface_default.xml` for face detection.
- Built using **CMake**, tested with **Visual Studio 2022** on Windows.
- Unit testing enabled via **GoogleTest** (see `README_tests.md`).
- _Ensure your **PowerShell** has permissions to execute scripts and manage processes._

---

## How to build and run

### _Prerequisites_
- **CMake** (tested with version ≥ 3.20)
- **Visual Studio 2019 or later** (using `vc16` toolset)
- **OpenCV 4.x** installed and built locally
- **GoogleTest** (optional, for unit testing)
- A **Windows PC** (tested on Windows 11 x64)

Ensure the following environment variables or paths are set:
- `OpenCV_DIR` points to `C:\opencv\build\x64\vc16\lib`
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
### Run the Game:
#### Option 1:
If all files are already in place:
```powershell
.\Debug\FaceDetectionStarter.exe
```
#### Option 2:
If `Error: Could not load Haar cascade file.` occurs:

The program expects the `haarcascade_frontalface_default.xml` to be in the **same directory** as your `.exe` (typically `build\Debug`).

Copy the Haar cascade file and the OpenCV DLLs there:
```powershell
cd Debug
Copy-Item "C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml" -Destination "."
Copy-Item "C:\opencv\build\x64\vc16\bin\*.dll" -Destination "."
.\FaceDetectionStarter.exe
```
### Run Unit Tests
For unit tests, refer to the separate test documentation:
```
/tests/README_tests.md
```

---

### Notes
> Haar cascade XML and DLLs must be copied to the .exe directory (build/Debug/).

> Webcam must not be blocked by other applications.

> If no face is found, the last detected face position is reused.

> The game can be exited anytime via ESC.

> The game will not start if input is invalid (e.g., negative object count or empty name).

## Authors & Acknowledgments
Developed by: Paulina Bayha & Sara Zor

DHBW Stuttgart- ITA24| OOP in C++ (2025)

---
Program builds and runs without error on a Windows machine with properly configured dependencies.

No responsibility is taken for external libraries (OpenCV).




