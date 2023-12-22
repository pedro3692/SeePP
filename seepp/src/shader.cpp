#include <format>
#include <glad/gl.h>
#include <iostream>

#include "shader.h"

namespace SeePP {

Shader::Shader(ShaderType type, const char *code) : m_type(type) {
  if (m_type == ShaderType::None) {
    std::cout << "ERROR::SHADER::CONSTRUCTOR::TYPE_NOT_SPECIFIED\n";
    return;
  }

  m_id = glCreateShader((uint32_t)m_type);
  glShaderSource(m_id, 1, &code, nullptr);
  glCompileShader(m_id);

  int success;
  char infoLog[512];
  glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
    std::cout << std::format("ERROR::SHADER::{1}::COMPILATION_FAILED\n{0}\n",
                             infoLog, ShaderTypeToString(m_type));
  }
  std::cout << std::format("INFO::SHADER::{}::{}::CREATED\n",
                           ShaderTypeToString(type), m_id);
}

Shader::~Shader() {
  if (!m_id) {
      std::cout << std::format("ERROR::SHADER::{}::{}::DESTRUCTOR::NOT_INITIALIZED\n",
                             ShaderTypeToString(m_type), m_id);
    return;
  }

  glDeleteShader(m_id);
  std::cout << std::format("INFO::SHADER::{}::{}::DELETED\n",
                           ShaderTypeToString(m_type), m_id);
}

uint32_t Shader::id() const { return m_id; }

} // namespace SeePP
