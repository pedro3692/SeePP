#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <cstdint>

namespace SeePP {

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void Bind() const;

private:
  uint32_t m_id;
};

} // namespace SeePP

#endif // VERTEX_ARRAY_H_
