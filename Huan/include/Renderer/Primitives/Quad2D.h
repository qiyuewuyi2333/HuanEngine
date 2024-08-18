#pragma once

#include "Huan/Core.h"

#include "Renderer/Primitives/Shape2D.h"
#include "Renderer/Primitives/Color.h"

namespace Huan
{
class HUAN_API Quad2D : public Shape2D
{
  public:
    Quad2D() = delete;
    Quad2D(const Quad2D& square);
    Quad2D(const Point2D& center, const glm::vec2& side = {1.0f, 1.0f},
             const Color& color = {1.0f, 1.0f, 1.0f, 1.0f});
    ~Quad2D() = default;

    constexpr double getArea() const;
    constexpr double getPerimeter() const;

  public:
    Point2D myCenterPostion;
    glm::vec2 mySideLength;
    Color myColor;
};

} // namespace Huan