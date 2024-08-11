#pragma once
#include "RendererAPI.h"
namespace Huan
{
class RenderCommand
{
  public:
    RenderCommand();
    void init();
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setClearColor(const glm::vec4& color);
    void clear();
    void drawIndexed(const VertexArray& vertexArray);
    void setRendererAPIInstance(RendererAPI* api);

  private:
    std::unique_ptr<RendererAPI> myRendererAPI;
};

} // namespace Huan