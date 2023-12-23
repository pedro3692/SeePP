#pragma once

#include <cstdint>

namespace SeePP {

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  void AttachShader(uint32_t shader_id) const;
  void Link() const;
  void Use() const;

private:
  uint32_t m_id = 0;
};

} // namespace SeePP
