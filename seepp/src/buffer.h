#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <cstdint>
#include <glad/gl.h>

namespace SeePP {

enum class BufferType {
  None,
  Vertex = GL_VERTEX_ARRAY,
  Index = GL_ELEMENT_ARRAY_BUFFER,
};

enum class BindType {
  None,
  Stream = GL_STREAM_DRAW,
  Static = GL_STATIC_DRAW,
  Dynamic = GL_DYNAMIC_DRAW,
};

class Buffer {
public:
  Buffer(BufferType type);
  ~Buffer();

  void Bind() const;
  void BindData(void *vertices, int64_t size, BindType bind_type) const;

private:
  BufferType m_type = 0;
  uint32_t m_id = 0;
};

} // namespace SeePP
#endif // VERTEX_BUFFER_H_
