#pragma once

namespace Huan
{
class IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getCount() const = 0;
};
} // namespace Huan