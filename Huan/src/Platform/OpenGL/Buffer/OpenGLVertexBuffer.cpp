#include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
#include "util/Log.h"

namespace Huan
{

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
    HUAN_PROFILE_FUNCTION();
    myCount = size / sizeof(float);
    glCreateBuffers(1, &myRendererID);
    glNamedBufferData(myRendererID, size, nullptr, GL_DYNAMIC_DRAW);
    HUAN_CORE_TRACE("OpenGL VertexBuffer created, ID: {0}", myRendererID);
}
/**
 * @brief Construct a new OpenGL Vertex Buffer object, and upload data to GPU. Not with Bind.
 *
 * @param vertices
 * @param size
 */
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
    HUAN_PROFILE_FUNCTION();
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
    HUAN_PROFILE_FUNCTION();
    glDeleteBuffers(1, &myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexBuffer deleted, ID: {0}", myRendererID);
}
/**
 * @brief Bind the OpenGL Array Buffer with cur ID
 *
 */
void OpenGLVertexBuffer::bind() const
{
    HUAN_PROFILE_FUNCTION();
    glBindBuffer(GL_ARRAY_BUFFER, myRendererID);
    // HUAN_CORE_TRACE("OpenGL VertexBuffer binded, ID: {0}", myRendererID);
}
/**
 * @brief Set the data of OpenGL Array Buffer with cur ID
 *
 * @param data
 * @param size
 */
void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
{
    HUAN_PROFILE_FUNCTION();
    glNamedBufferSubData(myRendererID, 0, size, data);
    // HUAN_CORE_TRACE("OpenGL VertexBuffer set data, ID: {0}", myRendererID);
}
/**
 * @brief Set the layout of OpenGL Array Buffer
 *
 * @param layout
 */
void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
{
    myVertexNumber = myCount / layout.getNumber();
    myLayout = layout;
}
/**
 * @brief Unbind the OpenGL Array Buffer with cur ID
 *
 */
void OpenGLVertexBuffer::unbind() const
{
    HUAN_PROFILE_FUNCTION();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    HUAN_CORE_TRACE("OpenGL VertexBuffer unbinded, ID: {0}", myRendererID);
}
constexpr uint32_t OpenGLVertexBuffer::getCount() const
{
    return myCount;
}
constexpr const BufferLayout& OpenGLVertexBuffer::getLayout() const
{
    return myLayout;
}
constexpr uint32_t OpenGLVertexBuffer::getMyRendererID() const
{
    return myRendererID;
}
constexpr uint32_t OpenGLVertexBuffer::getMyVertexNumber() const
{
    return myVertexNumber;
}

} // namespace Huan