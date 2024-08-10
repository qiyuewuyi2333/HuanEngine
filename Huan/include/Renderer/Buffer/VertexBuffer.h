#pragma once

namespace Huan
{
class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setData(const void* data, uint32_t size) = 0;
    virtual uint32_t getCount() const = 0;

};

} // namespace Huan