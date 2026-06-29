# OpenGL C++ Project

A simple OpenGL project configured for Visual Studio Code using C++, GLFW, and GLAD.

## Prerequisites

- **MinGW-w64** (with `g++`, `gdb`, and `make` installed via MSYS2 or similar)
- **VS Code** with the **C/C++ Extension** (Microsoft) installed.
- Ensure that `C:\msys64\mingw32\bin` (or your equivalent MinGW bin folder) is added to your Windows Environment `PATH` to run the executable outside of VS Code.

## How Its been drawn
**OpenGL** is a **"State Machine."** It remembers what you clicked on or activated last. When you call **glDrawArrays**, it simply looks at whatever is currently active (bound) in its memory slots and uses that data.

### Step 1: You copied the data into GPU Memory
``` C++
glBindBuffer(GL_ARRAY_BUFFER, buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```
By binding buffer, you told OpenGL: "Keep this specific buffer active." Then glBufferData shoved your triangle array into that active slot.

### Step 2: You defined the blueprint for the active buffer
``` C++
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```
glVertexAttribPointer does not take a buffer ID as an argument. Instead, it implicitly says: "Hey, whatever buffer is currently bound to GL_ARRAY_BUFFER (which is your triangle buffer), link its data layout to Shader Attribute Location 0."

### Step 3: The Render Loop (The Draw Call)
```C++
glUseProgram(shader);
glDrawArrays(GL_TRIANGLES, 0, 3);
```
When glDrawArrays is called, it triggers the active shader (shader).

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
