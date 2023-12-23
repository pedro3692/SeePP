#include <format>
#include <glad/gl.h>
#include <iostream>
#include <spdlog/spdlog.h>

#include "shader_program.h"

namespace SeePP {

ShaderProgram::ShaderProgram() {
  m_id = glCreateProgram();
  SPDLOG_DEBUG("shader_program [{}] created", m_id);
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(m_id);
  SPDLOG_DEBUG("shader_program [{}] deleted", m_id);
}

void ShaderProgram::AttachShader(uint32_t shader_id) const {
  glAttachShader(m_id, shader_id);
  SPDLOG_DEBUG("shader_program [{}] shader [{}] attached", m_id, shader_id);
}

void ShaderProgram::Link() const {
  glLinkProgram(m_id);

  int success;
  char infoLog[512];
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_id, 512, NULL, infoLog);
    SPDLOG_ERROR("could not link shader_program [{}]: {}", m_id, infoLog);
  }
}

void ShaderProgram::Use() const { glUseProgram(m_id); }

} // namespace SeePP
