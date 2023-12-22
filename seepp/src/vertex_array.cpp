#include "glad/gl.h"

#include "vertex_array.h"
#include <format>
#include <iostream>

namespace SeePP {

VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_id);
  std::cout << std::format("INFO::VERTEX_ARRAY::{}::CREATED\n", m_id);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_id);
  std::cout << std::format("INFO::VERTEX_ARRAY::{}::DELETED\n", m_id);
}

void VertexArray::Bind() const { glBindVertexArray(m_id); }

void VertexArray::BindAttributePointer(uint32_t index, int32_t count, DataType type,
                                bool normalize, int stride,
                                const void *pointer) const {
  glVertexAttribPointer(index, count, (GLenum)type, normalize, stride, pointer);
  glEnableVertexAttribArray(index);
}

} // namespace SeePP
