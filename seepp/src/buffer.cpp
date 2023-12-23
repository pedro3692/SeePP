#include <cstdint>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include "buffer.h"

namespace SeePP {

Buffer::Buffer() {
  glGenBuffers(1, &m_id);
  SPDLOG_DEBUG("vbo [{}] created", m_id);
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &m_id);
  SPDLOG_DEBUG("vbo [{}] deleted", m_id);
}

void Buffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void Buffer::BindData(void *vertices, int64_t size, BindType mode) const {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, (GLenum)mode);
}

} // namespace SeePP
