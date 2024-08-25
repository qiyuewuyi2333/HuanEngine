#pragma once

namespace Huan
{
struct TextureProperty
{
    unsigned int width;
    unsigned int height;
    unsigned int channels;
    unsigned int format;
    unsigned int type;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int minFilter;
    unsigned int magFilter;
    unsigned int internalFormat;
    unsigned int border;
    unsigned int mipmap;
    unsigned int srgb;
    unsigned int flip;
    bool anistropic;
};

class Texture
{
  public:
    virtual ~Texture() = default;

    virtual constexpr unsigned int getHeight() const = 0;
    virtual constexpr unsigned int getWidth() const = 0;
    virtual constexpr unsigned int getMyID() const = 0;
    virtual const std::string& getPath() const = 0;

    virtual void bind(unsigned int slot = 0) const = 0;
    virtual void setData(void* data, unsigned int size) = 0;
};

} // namespace Huan