#include <cstdint>
#include <format>
#include <glad/gl.h>
#include <iostream>

#include "vertex_buffer.h"

namespace SeePP {

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_id);
  std::cout << std::format("INFO::VERTEXBUFFER::{}::CREATED\n", m_id);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_id);
  std::cout << std::format("INFO::VERTEXBUFFER::{}::DELETED\n", m_id);
}

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VertexBuffer::BindData(void *vertices, int64_t size, DrawMode mode) const {
  glBufferData(GL_ARRAY_BUFFER, size, vertices, (GLenum)mode);
}

void VertexBuffer::BindAttribute(uint32_t index, int32_t count,
                                 AttributeType type, bool normalize, int stride,
                                 const void *pointer) const {
  glVertexAttribPointer(index, count, (GLenum)type, normalize, stride, pointer);
  glEnableVertexAttribArray(index);
}

} // namespace SeePP
