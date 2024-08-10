#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "util/Log.h"
#include "Renderer/Buffer/BufferLayout.h"

namespace Huan
{
static GLenum shaderTypeToGLType(const ShaderDataType& type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    }
    HUAN_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexArray created, ID: {0}", myRendererID);
}
OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexArray deleted, ID: {0}", myRendererID);
}
void OpenGLVertexArray::bind() const
{
    glBindVertexArray(myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexArray binded, ID: {0}", myRendererID);
}
void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
    HUAN_CORE_TRACE("OpenGL VertexArray unbinded, ID: {0}", myRendererID);
}
/**
 * @brief Set the VertexArray's Layout pointer with the VertexBuffer's Layout
 *
 * @param vertexBuffer
 */
void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    HUAN_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "VertexBuffer has no layout!");
    bind();
    vertexBuffer->bind();
    myVertexBufferIndex = 0;
    const auto& layout = vertexBuffer->getLayout();
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(myVertexBufferIndex);
        glVertexAttribPointer(myVertexBufferIndex, element.getComponentCount(), shaderTypeToGLType(element.type),
                              element.shouldNormalized ? GL_TRUE : GL_FALSE, layout.getStride(),
                              (const void*)element.offset);
        myVertexBufferIndex++;
    }
    myVertexBuffers.push_back(vertexBuffer);
    HUAN_CORE_TRACE("OpenGL VertexArray {0} add VertexBuffer, ID: {1}", myRendererID, vertexBuffer->getMyRendererID());
}
void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    myIndexBuffer = indexBuffer;
    HUAN_CORE_TRACE("OpenGL VertexArray, ID: {0} set IndexBuffer, ID: {1}", myRendererID,
                    indexBuffer->getMyRendererID());
}
constexpr uint32_t OpenGLVertexArray::getMyRendererID() const
{
    return myRendererID;
}
const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
{
    return myVertexBuffers;
}
const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
{
    return myIndexBuffer;
}
} // namespace Huan