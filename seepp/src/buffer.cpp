#include <cstdint>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include "buffer.h"

namespace SeePP {

Buffer::Buffer(BufferType type)
  : m_type(type)
{
  if (m_type == BufferType::None) {
    SPDLOG_ERROR("buffer cannot have None type");
    return;
  }

  glGenBuffers(1, &m_id);
  SPDLOG_DEBUG("{}_buffer[{}] created", BufferTypeToString(m_type), m_id);
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &m_id);
  SPDLOG_DEBUG("{}_buffer[{}] deleted", BufferTypeToString(m_type), m_id);
}

void Buffer::Bind() const {
  glBindBuffer((GLenum)m_type, m_id);
  SPDLOG_DEBUG("{}_buffer[{}] bound", BufferTypeToString(m_type), m_id);
}

void Buffer::BindData(const void *data, int size, BindType mode) const {
  glBufferData((GLenum)m_type, size, data, (GLenum)mode);
  SPDLOG_DEBUG("{} bytes of data bound to {}_buffer[{}]", size,
               BufferTypeToString(m_type), m_id);
}

} // namespace SeePP
