#include <format>
#include <glad/gl.h>
#include <iostream>
#include <spdlog/spdlog.h>

#include "shader.h"

namespace SeePP {

Shader::Shader(ShaderType type, const char *code) : m_type(type) {
  if (m_type == ShaderType::None) {
    SPDLOG_ERROR("shader type not specified");
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
    SPDLOG_ERROR("{}_shader[{}] compilation failed", ShaderTypeToString(m_type), infoLog);
  }
  SPDLOG_DEBUG("{}_shader[{}] created", ShaderTypeToString(m_type), m_id);
}

Shader::~Shader() {
  if (!m_id) {
    SPDLOG_ERROR("uninitialized {}_shader cannot be deleted", ShaderTypeToString(m_type));
    return;
  }

  glDeleteShader(m_id);
  SPDLOG_DEBUG("{}_shader[{}] deleted", ShaderTypeToString(m_type), m_id);
}

uint32_t Shader::id() const { return m_id; }

} // namespace SeePP
