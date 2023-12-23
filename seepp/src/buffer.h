#pragma once
#include <cstdint>
#include <glad/gl.h>

namespace SeePP {

enum class BufferType {
  None,
  Vertex = GL_VERTEX_ARRAY,
  Index = GL_ELEMENT_ARRAY_BUFFER,
};

constexpr const char *BufferTypeToString(BufferType type) {
  switch (type) {
  case BufferType::None:
    return "none";
  case BufferType::Vertex:
    return "vertex";
  case BufferType::Index:
    return "index";
  }
}

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
  void BindData(const void *vertices, int size, BindType bind_type) const;

private:
  BufferType m_type = BufferType::None;
  uint32_t m_id = 0;
};

} // namespace SeePP
