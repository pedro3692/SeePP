#ifndef FRAGMENT_SHADER_H_
#define FRAGMENT_SHADER_H_

#include <cstdint>

class FragmentShader {
public:
  FragmentShader(const char* code);
  ~FragmentShader();

  uint32_t id() const;

private:
  uint32_t m_id = 0;
};
#endif // FRAGMENT_SHADER_H_
