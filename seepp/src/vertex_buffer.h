#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <cstdint>
#include <glad/gl.h>

namespace SeePP {

enum class DrawMode {
  None,
  Stream = GL_STREAM_DRAW,
  Static = GL_STATIC_DRAW,
  Dynamic = GL_DYNAMIC_DRAW,
};

class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

  void BindData(float *vertices, DrawMode mode);

private:
  uint32_t m_id = 0;
};

} // namespace SeePP
#endif // VERTEX_BUFFER_H_
