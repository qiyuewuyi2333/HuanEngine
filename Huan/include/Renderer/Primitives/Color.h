#pragma once
#include "glm/glm.hpp"

namespace Huan
{
class Color
{
  public:
    Color() = delete;
    Color(float r, float g, float b, float a = 1.0f) : myColorValue(r, g, b, a)
    {
    }
  public:
    glm::vec4 myColorValue;
};
} // namespace Huan
