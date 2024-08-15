#pragma once
#include "Renderer/Buffer/IndexBuffer.h"
#include "Huan/Core.h"

namespace Huan
{
class HUAN_API OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void bind() const override;
    void unbind() const override;

    uint32_t getCount() const override;
    uint32_t getMyRendererID() const override;
    uint32_t getType() const override;

  private:
    uint32_t myRendererID;
    uint32_t myCount;
};
} // namespace Huan