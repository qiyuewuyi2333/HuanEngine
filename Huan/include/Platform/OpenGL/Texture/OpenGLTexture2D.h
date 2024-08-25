#pragma once

#include "Renderer/Texture/Texture2D.h"
#include "util/Log.h"

namespace Huan
{

class HUAN_API OpenGLTexture2D : public Texture2D
{
  public:
    OpenGLTexture2D(const std::string& path);
    OpenGLTexture2D(uint32_t width, uint32_t height);
    ~OpenGLTexture2D() override;
    virtual void bind(uint32_t slot = 0) const override;
    virtual void setData(void* data, unsigned int size) override;

    virtual uint32_t getWidth() const override
    {
        return myProperty->width;
    }
    virtual uint32_t getHeight() const override
    {
        return myProperty->height;
    }
    virtual uint32_t getMyID() const override
    {
        return myRendererID;
    };
    virtual const std::string& getPath() const override
    {
        return myPath;
    }

  private:
    Ref<TextureProperty> myProperty = std::make_shared<TextureProperty>();
    uint32_t myRendererID;
    std::string myPath;
};
} // namespace Huan