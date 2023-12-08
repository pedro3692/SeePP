#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_
#include <cstdint>

class VertexShader {
public:
  VertexShader(const char* code);
  ~VertexShader();

  uint32_t id() const;

private:
  uint32_t m_id = 0;
};
#endif // VERTEX_SHADER_H_
