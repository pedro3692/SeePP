#include <cstdint>
#include <glad/gl.h>
#include <iostream>

#include "vertex_buffer.h"

namespace SeePP {

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_id);
  std::cout << "buffer id: " << m_id << " created\n";
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_id);
	std::cout << "buffer id:" << m_id << " deleted\n";
}

void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VertexBuffer::BindData(float *vertices, DrawMode mode) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, (GLenum)mode);
}

void VertexBuffer::BindAttribute(uint32_t index, int32_t size,
                                 AttributeType type, bool normalize, int stride,
                                 const void *pointer) {
  glVertexAttribPointer(index, size, (GLenum)type, normalize, stride, pointer);
  glEnableVertexAttribArray(index);
}

} // namespace SeePP
