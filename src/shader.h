#pragma once

#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;

    public:
        Shader(const std::string& filePath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    private:
        unsigned int getUniformLocation(const std::string& name);
};