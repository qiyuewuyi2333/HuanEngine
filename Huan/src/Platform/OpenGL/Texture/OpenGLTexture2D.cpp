#include "Platform/OpenGL/Texture/OpenGLTexture2D.h"
#include "util/StbImage.h"
#include <cstdint>

namespace Huan
{
OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : myPath(path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);

    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    HUAN_CORE_ASSERT(data, "Failed to load image");
    myWidth = width;
    myHeight = height;
    switch (channels)
    {
    case 1:
        myFormat = GL_R;
        mySizedFormat = GL_R8;
        break;
    case 3:
        myFormat = GL_RGB;
        mySizedFormat = GL_RGB8;
        break;
    case 4:
        myFormat = GL_RGBA;
        mySizedFormat = GL_RGBA8;
        break;
    default:
        HUAN_CORE_ASSERT(false, "Unsupported format");
    }
    
    glCreateTextures(GL_TEXTURE_2D, 1, &myRendererID);
    glTextureStorage2D(myRendererID, 1, mySizedFormat, myWidth, myHeight);
    glTextureParameteri(myRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(myRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureSubImage2D(myRendererID, 0, 0, 0, myWidth, myHeight, myFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateTextureMipmap(myRendererID);
    HUAN_CORE_TRACE("Loaded image {0} with width {1} and height {2}", path, width, height);
}
OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &myRendererID);
    HUAN_CORE_TRACE("Destroyed texture, ID: {0}, path: {1}", myRendererID, myPath);
}
void OpenGLTexture2D::bind(uint32_t slot) const
{
    glBindTextureUnit(slot, myRendererID);
    // HUAN_CORE_TRACE("Bind texture, ID: {0}, path: {1}, slot: {2}", myRendererID, myPath, slot);
}
} // namespace Huan