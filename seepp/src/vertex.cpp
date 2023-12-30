#include "vertex.h"
#include <array>
#include <spdlog/spdlog.h>

namespace SeePP {

Vertex::Vertex(glm::vec3 pos)
    : m_pos(pos) {
  SPDLOG_DEBUG("vertex[{}, {}, {}] created", m_pos.x, m_pos.y, m_pos.z);
}

Vertex::Vertex(glm::vec3 pos, glm::vec4 color)
    : m_pos(pos), m_color(color) {
  SPDLOG_DEBUG("vertex[{}, {}, {}] created", m_pos.x, m_pos.y, m_pos.z);
}

Vertex::Vertex(glm::vec3 pos, glm::vec4 color, glm::vec2 tex_pos)
    : m_pos(pos), m_color(color), m_tex_pos(tex_pos) {
  SPDLOG_DEBUG("vertex[{}, {}, {}] created", m_pos.x, m_pos.y, m_pos.z);
}

Vertex& Vertex::operator=(const Vertex& other) noexcept {
  m_pos = other.m_pos;
  m_color = other.m_color;
  m_tex_pos = other.m_tex_pos;

  return *this;
}

std::array<float, 9> Vertex::ToArray() const {
  return std::array<float, 9>{m_pos.x,   m_pos.y,     m_pos.z,
                               m_color.r, m_color.g,   m_color.b,
                               m_color.a, m_tex_pos.x, m_tex_pos.y};
}

} // namespace SeePP
