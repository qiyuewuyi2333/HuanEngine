#include "Renderer/Primitives/Quad2D.h"

namespace Huan
{


Quad2D::Quad2D(const Quad2D& square)
    :myCenterPostion(square.myCenterPostion),mySideLength(square.mySideLength), myColor(square.myColor)
{
    
}

Quad2D::Quad2D(const Point2D& center, const glm::vec2& side, const Color& color)
    :myCenterPostion(center),mySideLength(side), myColor(color)
{
    
}

constexpr double Quad2D::getArea() const
{
    return mySideLength.x * mySideLength.y;
}

constexpr double Quad2D::getPerimeter() const
{
    return 2 * (mySideLength.x + mySideLength.y);
}


}
