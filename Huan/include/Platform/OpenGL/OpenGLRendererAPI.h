#pragma once

#include "Renderer/RendererAPI.h"
namespace Huan
{
class OpenGLRendererAPI : public RendererAPI
{
  public:
    OpenGLRendererAPI() = default;
    virtual ~OpenGLRendererAPI() = default;
    virtual void init() override;
    virtual void setClearColor(const glm::vec4& color) override;
    virtual void clear() override;
    virtual void drawIndexed(const VertexArray& vertexArray) override;
    virtual void enableBlend() override;
    virtual void enableDepthTest() override;
};
} // namespace Huan