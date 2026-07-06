#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
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
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    // Setup ImGui binding
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    ImGui_ImplGlfwGL3_Init(window, true);

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
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

        float projScale = 1;

        glm::mat4 view(1.0f); 
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        // shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/texture/awesome.png");
        texture.Bind();

        shader.Unbind();
        vao.Unbind();
        vbo.Unbind();
        ibo.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;   
        
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);    
        
        glm::vec3 cameraPos(0.0f, 0.0f, 0.0f);
        glm::vec3 TransformA(-1.0f, 0.0f, 0.0f);
        glm::vec3 TransformB( 1.0f, 0.0f, 0.0f);
        
        
        // Render loop
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            ImGui_ImplGlfwGL3_NewFrame();

            // Input handling
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);


            // ImGui debug window
            {
                
                ImGui::Checkbox("Another Window", &show_another_window);
                ImGui::SameLine();
                ImGui::Checkbox("Demo Window", &show_demo_window);

                ImGui::SliderFloat("Zoom", &projScale, 1.0f, 10.0f);
                ImGui::SliderFloat3("Object A", &TransformA.x, -5.0f, 5.0f);
                ImGui::SliderFloat3("Object B", &TransformB.x, -5.0f, 5.0f);

                ImGui::SliderFloat3("Camera Position", &cameraPos.x, -5.0f, 5.0f);

                ImGui::Text("Object Position: (%.1f, %.1f, %.1f)", cameraPos.x, cameraPos.y, cameraPos.z);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            if (show_another_window)
            {
                // ImGui::ShowDemoWindow(&show_demo_window);
                ImGui::Begin("Another Window", &show_another_window);
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
            if (show_demo_window)
            {
                ImGui::ShowDemoWindow(&show_demo_window);
            }
            
            glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
            renderer.Clear();

            glm::mat4 proj = glm::ortho(
                -aspectRatio * projScale, 
                aspectRatio  * projScale,
                -1.0f * projScale, 
                1.0f * projScale, 
                -1.0f, 1.0f
            ); 

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), TransformA); 
                glm::mat4 mvp = proj * view * model; 

                shader.Bind();
                shader.SetUniform1i("u_Texture", 0);
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(vao, ibo, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), TransformB); 
                glm::mat4 mvp = proj * view * model; 

                shader.Bind();
                shader.SetUniform1i("u_Texture", 0);
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(vao, ibo, shader);
            }

            view = glm::translate(glm::mat4(1.0f), -cameraPos);
            glm::mat4 mvp = proj * view * glm::mat4(0.0f);
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    
    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}