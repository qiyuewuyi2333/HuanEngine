#pragma once

namespace Huan
{
class Texture
{
  public:
    virtual ~Texture() = default;

    virtual constexpr unsigned int getHeight() const = 0;
    virtual constexpr unsigned int getWidth() const = 0;
    virtual constexpr unsigned int getMyID() const = 0;

    virtual void bind(unsigned int slot = 0) const = 0;
};

} // namespace Huan