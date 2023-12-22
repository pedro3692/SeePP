#include <format>
#include <glad/gl.h>
#include <iostream>

#include "shader_program.h"

namespace SeePP {

ShaderProgram::ShaderProgram() {
  m_id = glCreateProgram();
  std::cout << std::format("INFO::SHADER_PROGRAM::{}::CREATED\n", m_id);
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(m_id);
  std::cout << std::format("INFO::SHADER_PROGRAM::{}::DELETED\n", m_id);
}

void ShaderProgram::AttachShader(uint32_t shader_id) const {
  glAttachShader(m_id, shader_id);
}

void ShaderProgram::Link() const {
  glLinkProgram(m_id);

  int success;
  char infoLog[512];
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_id, 512, NULL, infoLog);
    std::cout << std::format("ERROR::SHADER::PROGRAM::LINK_FAILED\n{}\n",
                             infoLog);
  }
}

void ShaderProgram::Use() const { glUseProgram(m_id); }

} // namespace SeePP
