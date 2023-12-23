#include <cstdint>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include "vertex_buffer.h"

namespace SeePP {

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_id);
  SPDLOG_DEBUG("vbo [{}] created", m_id);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_id);
  SPDLOG_DEBUG("vbo [{}] deleted", m_id);
}

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VertexBuffer::BindData(void *vertices, int64_t size, BindType mode) const {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, (GLenum)mode);
}

} // namespace SeePP
