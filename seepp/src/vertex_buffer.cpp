#include <glad/gl.h>

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}
