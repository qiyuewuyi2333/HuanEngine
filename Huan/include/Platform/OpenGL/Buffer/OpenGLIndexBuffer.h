#pragma once
#include "Renderer/Buffer/IndexBuffer.h"

namespace Huan
{
class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void bind() const override;
    void unbind() const override;

    uint32_t getCount() const override;

  private:
    uint32_t myRendererID;
    uint32_t myCount;
};
} // namespace Huan