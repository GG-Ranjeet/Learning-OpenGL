# OpenGL C++ Project

A simple OpenGL project configured for Visual Studio Code using C++, GLFW, and GLAD.

## Prerequisites

- **MinGW-w64** (with `g++`, `gdb`, and `make` installed via MSYS2 or similar)
- **VS Code** with the **C/C++ Extension** (Microsoft) installed.
- Ensure that `C:\msys64\mingw32\bin` (or your equivalent MinGW bin folder) is added to your Windows Environment `PATH` to run the executable outside of VS Code.

## Project Structure

- `src/` - Contains your source files (`main.cpp`, `glad.c`).
- `include/` - Contains the headers for your dependencies (GLFW, GLAD).
- `lib/` - Contains the precompiled `.a` library files for GLFW.
- `.vscode/` - Contains VS Code configuration files:
  - `tasks.json` - Configures the `g++` build task.
  - `launch.json` - Configures the C++ debugger to easily run and debug the project in VS Code.

## How to Build and Run

1. Open the project in VS Code.
2. Go to the **Run and Debug** view (`Ctrl+Shift+D`).
3. Select **"Launch OpenGL Project"** from the dropdown at the top.
4. Click the green **Play** button (or press `F5`). 

This will automatically compile the code using `tasks.json` and launch the window with the debugger attached!

## Dependencies

- **GLFW 3**: For creating the window and handling input.
- **GLAD**: For loading OpenGL function pointers.
