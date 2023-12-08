
#include <glad/gl.h>
#include <iostream>
#include <format>

#include "fragment_shader.h"

FragmentShader::FragmentShader(const char* code)
{
    m_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_id, 1, &code, nullptr);
    glCompileShader(m_id);

    int success;
    char infoLog[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << std::format("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}\n", infoLog);
    }
}

FragmentShader::~FragmentShader()
{
    if (m_id)
        glDeleteShader(m_id);
}

uint32_t FragmentShader::id() const
{
    return m_id;
}
