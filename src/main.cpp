#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

ShaderProgramSource ParseShader(std::string filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)shaderType] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShader(const int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1); // Enable V-Sync

    // Create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD before calling any OpenGL function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    {
        float vertices[] = {
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        VertexBuffer vbo(vertices, sizeof(vertices));
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

        ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        std::cout << "Vertex Shader Source:\n"
                  << source.VertexSource << std::endl;
        std::cout << "Fragment Shader Source:\n"
                  << source.FragmentSource << std::endl;

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);

        glUseProgram(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        int location = glGetUniformLocation(shader, "u_Color");
        float r = 0.0f;
        float increment = 0.05f;
        float timeValue = glfwGetTime();

        // Render loop
        while (!glfwWindowShouldClose(window))
        {
            // Input handling
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            glUseProgram(shader);
            timeValue = glfwGetTime();
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            float redValue = (cos(timeValue) / 2.0f) + 0.5f;
            float blueValue = (cos(timeValue) / 2.0f) + 0.5f;

            glUniform4f(location, redValue, greenValue, blueValue, 1.0f);
            ibo.Bind();

            // before we had to do this
            // glBindBuffer(GL_ARRAY_BUFFER, buffer);
            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBindVertexArray(vao);

            // Rendering commands (Dark Teal Background)
            glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            // Swap buffers and poll IO events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glDeleteShader(shader);
    }
    glfwTerminate();

    return 0;
}