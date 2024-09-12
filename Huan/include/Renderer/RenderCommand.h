#pragma once
#include "RendererAPI.h"
namespace Huan
{
class HUAN_API RenderCommand
{
  public:
    RenderCommand();
    void init();
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setClearColor(const glm::vec4& color);
    void clear();
    void draw(const VertexArray& vertexArray);
    void drawIndexed(const VertexArray& vertexArray);
    void drawInstanced(const VertexArray& vertexArray, unsigned int instanceCount);
    void setRendererAPIInstance(RendererAPI* api);
    void enableDepthTest();
    void enableBlend();
    void setCursorMode(uint32_t mode);

  private:
    Scope<RendererAPI> myRendererAPI;
};

} // namespace Huan