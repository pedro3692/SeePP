#pragma once

#include <array>
#include <cstddef>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace SeePP {

class Vertex {
public:
  Vertex(const Vertex &other) = default;
  Vertex(glm::vec3 pos);
  Vertex(glm::vec3 pos, glm::vec4 color);
  Vertex(glm::vec3 pos, glm::vec4 color, glm::vec2 tex_pos);

  Vertex& operator=(const Vertex& other) noexcept;

  std::array<float, 9> ToArray() const;

  static const size_t size = sizeof(float) * 9;
  glm::vec3 m_pos={0.0f, 0.0f, 0.0f};
  glm::vec4 m_color = {0.0f, 0.0f, 0.0f, 0.0f};
  glm::vec2 m_tex_pos = {0.0f, 0.0f};
};

} // namespace SeePP
