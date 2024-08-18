#pragma once
#include "glm/glm.hpp"

namespace Huan
{
class Point2D : public glm::vec2
{
public:
    Point2D() = delete;
    Point2D(float x, float y) : glm::vec2(x, y) {}

};
} // namespace Huan
