#include "vertex_shader.h"
#include <glad/gl.h>
#include <iostream>
#include <format>

VertexShader::VertexShader(const char* code)
{
    m_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_id, 1, &code, nullptr);


    int success;
    char infoLog[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << std::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}\n", infoLog);
    }
}

VertexShader::~VertexShader()
{
    if (m_id)
        glDeleteShader(m_id);
}

uint32_t VertexShader::id() const
{
    return m_id;
}
