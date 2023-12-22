#include <cstdint>
#include <format>
#include <glad/gl.h>
#include <iostream>

#include "vertex_buffer.h"

namespace SeePP {

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_id);
  std::cout << std::format("INFO::VERTEX_BUFFER::{}::CREATED\n", m_id);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_id);
  std::cout << std::format("INFO::VERTEX_BUFFER::{}::DELETED\n", m_id);
}

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VertexBuffer::BindData(void *vertices, int64_t size, BindType mode) const {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, (GLenum)mode);
}

} // namespace SeePP
