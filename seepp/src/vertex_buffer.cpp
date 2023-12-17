#include <glad/gl.h>

#include "vertex_buffer.h"

namespace SeePP {

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::BindData(float *vertices, DrawMode mode)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, (GLenum)mode);
}

} // namespace SeePP
