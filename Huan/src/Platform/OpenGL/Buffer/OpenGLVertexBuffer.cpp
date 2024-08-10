#include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
#include "glad/glad.h"
#include "util/Log.h"
#include <cstdint>

namespace Huan
{
    /**
     * @brief Construct a new OpenGL Vertex Buffer object, and upload data to GPU. Not with Bind.
     * 
     * @param vertices 
     * @param size 
     */
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        myCount = size / sizeof(float);
        glCreateBuffers(1, &myRendererID);
        glNamedBufferData(myRendererID, size, vertices, GL_STATIC_DRAW);
        HUAN_CORE_TRACE("OpenGL VertexBuffer created, ID: {0}", myRendererID);
    }
    /**
     * @brief Destroy the OpenGL Vertex Buffer object
     * 
     */
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &myRendererID);
        HUAN_CORE_TRACE("OpenGL VertexBuffer deleted, ID: {0}", myRendererID);
    }
    /**
     * @brief Bind the OpenGL Array Buffer with cur ID
     * 
     */
    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, myRendererID);
        HUAN_CORE_TRACE("OpenGL VertexBuffer binded, ID: {0}", myRendererID);
    }
    /**
     * @brief Set the data of OpenGL Array Buffer with cur ID
     * 
     * @param data 
     * @param size 
     */
    void OpenGLVertexBuffer::setData(const void* data, uint32_t size) 
    {
        glNamedBufferSubData(myRendererID, 0, size, data);
        HUAN_CORE_TRACE("OpenGL VertexBuffer set data, ID: {0}", myRendererID);
    }
    /**
     * @brief Unbind the OpenGL Array Buffer with cur ID
     * 
     */
    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        HUAN_CORE_TRACE("OpenGL VertexBuffer unbinded, ID: {0}",myRendererID);
    }
    /**
     * @brief Get the count of OpenGL Array Buffer with cur ID
     * 
     * @return uint32_t 
     */
    uint32_t OpenGLVertexBuffer::getCount() const 
    {
        return myCount;
    }
}