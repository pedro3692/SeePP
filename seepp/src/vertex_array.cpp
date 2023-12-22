#include "glad/gl.h"

#include "vertex_array.h"

namespace SeePP {

  VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
  }

  VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
  }

  void VertexArray::Bind() const {
    glBindVertexArray(m_id);
  }

}
