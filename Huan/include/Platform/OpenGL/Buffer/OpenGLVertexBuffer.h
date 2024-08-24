#pragma once
#include "Renderer/Buffer/VertexBuffer.h"

namespace Huan
{
class HUAN_API OpenGLVertexBuffer : public VertexBuffer
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
    constexpr uint32_t getMyVertexNumber() const override;

  private:
    uint32_t myRendererID;
    uint32_t myCount;
    uint32_t myVertexNumber;
    BufferLayout myLayout;
};
} // namespace Huan