#pragma once

#include "Renderer/Buffer/BufferLayout.h"
namespace Huan
{
class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setData(const void* data, uint32_t size) = 0;
    virtual constexpr uint32_t getCount() const = 0;
    virtual constexpr uint32_t getMyRendererID() const = 0;

    virtual void setLayout(const BufferLayout& layout) = 0;
    virtual constexpr const BufferLayout& getLayout() const = 0;
};

} // namespace Huan