#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

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

#endif // SHADER_PROGRAM_H_
