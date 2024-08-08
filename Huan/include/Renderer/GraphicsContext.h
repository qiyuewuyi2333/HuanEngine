#pragma once

namespace Huan
{
class GraphicsContext
{
  public:
    GraphicsContext() = default;
    GraphicsContext(const GraphicsContext&) = delete;
    GraphicsContext(GraphicsContext&&) = delete;
    GraphicsContext& operator=(const GraphicsContext&) = delete;
    GraphicsContext& operator=(GraphicsContext&&) = delete;

    virtual void init() = 0;
    virtual void swapBuffers() = 0;

  private:
};
} // namespace Huan