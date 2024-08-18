#pragma once

#include "Renderer/Texture/Texture2D.h"

namespace Huan
{
    class HUAN_API OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();
        virtual void bind(uint32_t slot = 0) const override;
        virtual constexpr uint32_t getWidth() const override { return myWidth; }
        virtual constexpr uint32_t getHeight() const override { return myWidth; }
        virtual constexpr uint32_t getMyID() const override {return myRendererID; };

    private:
        uint32_t myRendererID;
        std::string myPath;
        uint32_t myWidth, myHeight;
        uint32_t myFormat;
        uint32_t mySizedFormat;
    };
}