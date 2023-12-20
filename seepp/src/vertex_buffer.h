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

enum class AttributeType {
  None,
  I8 = GL_BYTE,
  U8 = GL_UNSIGNED_BYTE,
  I16 = GL_SHORT,
  U16 = GL_UNSIGNED_SHORT,
  I32 = GL_INT,
  U32 = GL_UNSIGNED_INT,
  F32 = GL_FLOAT
};

class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

  void Bind();
  void BindData(float *vertices, DrawMode mode);
  void BindAttribute(uint32_t index, int32_t size, AttributeType type, bool normalize, int32_t stride, const void* pointer);

private:
  uint32_t m_id=0;
};

} // namespace SeePP
#endif // VERTEX_BUFFER_H_
