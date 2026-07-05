#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

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

    int width = 800;
    int height = 600;
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    /* 
        Hi
    */
    
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        VertexArray vao;
        VertexBufferLayout layout;
        VertexBuffer vbo(vertices, sizeof(vertices));

        layout.Push<float>(2); // Position
        layout.Push<float>(2); // Texture coordinates
        
        vao.AddBuffer(vbo, layout);

        IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

        int scale = 1;
        // this is the window aspect ratio and if we multiply it with the position matrix, we simply saying scale the position matrix by the aspect ratio of the window.
        glm::mat4 proj = glm::ortho(
            -aspectRatio * scale, 
            aspectRatio  * scale, // 
            -1.0f * scale, 
             1.0f * scale, 
            -1.0f, 1.0f
        ); 

        // translate the view/camera matrix
        glm::mat4 view(1.0f); 
        glm::mat4 model(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f)); // Move the view matrix to the right and up);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Move the model matrix to the right and up);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        // shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", model * view * proj);

        Texture texture("res/texture/awesome.png");
        texture.Bind();

        shader.Unbind();
        vao.Unbind();
        vbo.Unbind();
        ibo.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;        

        // Render loop
        while (!glfwWindowShouldClose(window))
        {
            // Input handling
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
            renderer.Clear();

            float currentLoopTime = (float)glfwGetTime();

            float redValue   = (std::sin(currentLoopTime * 1.0f) / 2.0f) + 0.5f;
            float greenValue = (std::cos(currentLoopTime * 1.5f) / 2.0f) + 0.5f;
            float blueValue  = (std::sin(currentLoopTime * 2.0f) / 2.0f) + 0.5f;

            // shader.SetUniform4f("u_Color", redValue, greenValue, blueValue, 1.0f);
            shader.SetUniform1i("u_Texture", 0); // Set the texture unit to 0

            renderer.Draw(vao, ibo, shader);
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();

    return 0;
}