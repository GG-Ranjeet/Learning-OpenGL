# OpenGL C++ Project

A simple OpenGL project configured for Visual Studio Code using C++, GLFW, and GLAD.

## Prerequisites

- **MinGW-w64** (with `g++`, `gdb`, and `make` installed via MSYS2 or similar)
- **VS Code** with the **C/C++ Extension** (Microsoft) installed.
- Ensure that `C:\msys64\mingw32\bin` (or your equivalent MinGW bin folder) is added to your Windows Environment `PATH` to run the executable outside of VS Code.

## Abstraction Layer & How It's Drawn
**OpenGL** is a **"State Machine."** It remembers what you clicked on or activated last. We have abstracted this raw OpenGL state machine into C++ classes to make it easier to manage:

### 1. VertexBuffer & IndexBuffer
Instead of calling raw `glBindBuffer` and `glBufferData`, we use `VertexBuffer` and `IndexBuffer` objects to upload our shape's data and drawing order into GPU memory.

### 2. VertexArray (VAO) & Layouts
The `VertexArray` binds together the raw data (from the `VertexBuffer`) with the layout blueprint (`VertexBufferLayout`). The layout tells OpenGL exactly how to read the raw bytes (e.g. "read 2 floats at a time for X and Y coordinates"). This linkage is saved inside the VAO.

### 3. Shaders
Shaders are written in a single `.shader` file and parsed dynamically using our custom `ParseShader` function, which splits out the Vertex and Fragment shaders before compiling them.

### 4. The Render Loop (The Draw Call)
```cpp
glUseProgram(shader);
vao.Bind();
ibo.Bind();
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
```
Inside the loop, we simply bind our shader, our VAO, and our IBO. When `glDrawElements` is called, OpenGL uses the bound index buffer to draw the shape using the layout defined in our active VAO!

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
