#pragma once

#include <cstdint>
#include <glad/gl.h>

namespace SeePP {

enum class DataType {
  None,
  I8 = GL_BYTE,
  U8 = GL_UNSIGNED_BYTE,
  I16 = GL_SHORT,
  U16 = GL_UNSIGNED_SHORT,
  I32 = GL_INT,
  U32 = GL_UNSIGNED_INT,
  F32 = GL_FLOAT,
  F64 = GL_DOUBLE
};

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void BindAttributePointer(uint32_t index, int32_t count, DataType type,
                     bool normalize, int32_t stride, const void *pointer) const;

private:
  uint32_t m_id;
};

} // namespace SeePP
