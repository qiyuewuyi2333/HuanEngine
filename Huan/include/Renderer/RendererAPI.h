#pragma once

#include "Renderer/VertexArray.h"

namespace Huan
{
class RendererAPI
{
  public:
    virtual void setClearColor(const glm::vec4& color) = 0;
    virtual void clear() = 0;
    virtual void drawIndexed(const VertexArray& vertexArray) = 0;
};
} // namespace Huan