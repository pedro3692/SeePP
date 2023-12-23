#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include "vertex_array.h"

namespace SeePP {

VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_id);
  SPDLOG_DEBUG("vertex_array[{}] created", m_id);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_id);
  SPDLOG_DEBUG("vertex_array[{}] deleted", m_id);
}

void VertexArray::Bind() const { glBindVertexArray(m_id); }

void VertexArray::BindAttributePointer(uint32_t index, int32_t count, DataType type,
                                bool normalize, int stride,
                                const void *pointer) const {
  glVertexAttribPointer(index, count, (GLenum)type, normalize, stride, pointer);
  glEnableVertexAttribArray(index);
  SPDLOG_DEBUG("vertex_array[{}] attrib pointer {} bound", m_id, index);
}

} // namespace SeePP
