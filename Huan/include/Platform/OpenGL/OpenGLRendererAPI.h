#pragma once

#include "Renderer/RendererAPI.h"
namespace Huan
{
class OpenGLRendererAPI : public RendererAPI
{
  public:
    OpenGLRendererAPI() = default;
    virtual ~OpenGLRendererAPI() = default;

    virtual void setClearColor(const glm::vec4& color) override;
    virtual void clear() override;
    virtual void drawIndexed(const VertexArray& vertexArray) override;
};
} // namespace Huan