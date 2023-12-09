
#include <cstdint>
#include <glad/gl.h>
#include <iostream>
#include <format>

#include "shader.h"

Shader::Shader(ShaderType type, const char* code)
    : m_type(type)
{
    m_id = glCreateShader((uint32_t)m_type);
    glShaderSource(m_id, 1, &code, nullptr);
    glCompileShader(m_id);

    int success;
    char infoLog[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << std::format("ERROR::SHADER::{1}::COMPILATION_FAILED\n{0}\n", infoLog, ShaderTypeToString(m_type));
    }
}

Shader::~Shader()
{
    if (m_id)
        glDeleteShader(m_id);
}

uint32_t Shader::id() const
{
    return m_id;
}
