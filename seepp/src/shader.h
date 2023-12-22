#ifndef SHADER_H_
#define SHADER_H_

#include <cstdint>
#include <glad/gl.h>

namespace SeePP {

enum class ShaderType {
  None = 0,
  Fragment = GL_FRAGMENT_SHADER,
  Vertex = GL_VERTEX_SHADER
};

constexpr const char *ShaderTypeToString(ShaderType st) {
  switch (st) {
  case ShaderType::None:
    return "None";
  case ShaderType::Fragment:
    return "Fragment";
  case ShaderType::Vertex:
    return "Vertex";
  }
}

class Shader {
public:
  Shader(ShaderType type, const char *code);
  ~Shader();

  uint32_t id() const;

private:
  uint32_t m_id = 0;
  ShaderType m_type = ShaderType::None;
};

} // namespace SeePP
#endif // SHADER_H_
