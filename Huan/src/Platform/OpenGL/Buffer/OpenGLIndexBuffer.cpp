#include "Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
#include "glad/glad.h"
#include "util/Log.h"
#include <cstdint>

namespace Huan
{
    /**
     * @brief Construct a new OpenGL Index Buffer object, and upload data to GPU. Not with Bind.
     * 
     * @param indices 
     * @param count 
     */
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    {
        myCount = count;
        glCreateBuffers(1, &myRendererID);
        glNamedBufferData(myRendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        HUAN_CORE_TRACE("OpenGL IndexBuffer created, ID: {0}", myRendererID);
    }
    /**
     * @brief Destroy the OpenGL Index Buffer object
     * 
     */
    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &myRendererID);
        HUAN_CORE_TRACE("OpenGL IndexBuffer deleted, ID: {0}", myRendererID);
    }
    /**
     * @brief Bind the OpenGL Element Array Buffer with cur ID
     * 
     */
    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myRendererID);
        HUAN_CORE_TRACE("OpenGL IndexBuffer binded, ID: {0}", myRendererID);
    }
    /**
     * @brief Unbind the OpenGL Element Array Buffer with cur ID
     * 
     */
    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        HUAN_CORE_TRACE("OpenGL IndexBuffer unbinded, ID: {0}", myRendererID);
    }
    /**
     * @brief Get the count of indices
     * 
     * @return uint32_t 
     */
    uint32_t OpenGLIndexBuffer::getCount() const
    {
        return myCount;
    }

}