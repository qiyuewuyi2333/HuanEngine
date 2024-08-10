#pragma once
#include "Renderer/Buffer/VertexBuffer.h"

namespace Huan
{
class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    // OpenGLVertexBuffer(uint32_t size);
    ~OpenGLVertexBuffer();

    void bind() const override;
    void setData(const void* data, uint32_t size) override;
    void unbind() const override;

    void setLayout(const BufferLayout& layout) override;
    constexpr const BufferLayout& getLayout() const override;
    constexpr uint32_t getCount() const override;
    constexpr uint32_t getMyRendererID() const override;

  private:
    uint32_t myRendererID;
    uint32_t myCount;
    BufferLayout myLayout;
};
} // namespace Huan