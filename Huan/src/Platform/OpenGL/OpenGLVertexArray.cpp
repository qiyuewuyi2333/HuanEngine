#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "util/Log.h"
#include "Renderer/Buffer/BufferLayout.h"

namespace Huan
{
static GLenum shaderTypeToGLType(const ShaderDataType& type)
{
    HUAN_PROFILE_FUNCTION();
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
    HUAN_PROFILE_FUNCTION();
    glCreateVertexArrays(1, &myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexArray created, ID: {0}", myRendererID);
}
OpenGLVertexArray::~OpenGLVertexArray()
{
    HUAN_PROFILE_FUNCTION();
    glDeleteVertexArrays(1, &myRendererID);
    HUAN_CORE_TRACE("OpenGL VertexArray deleted, ID: {0}", myRendererID);
}
void OpenGLVertexArray::bind() const
{
    HUAN_PROFILE_FUNCTION();
    glBindVertexArray(myRendererID);
    // HUAN_CORE_TRACE("OpenGL VertexArray binded, ID: {0}", myRendererID);
}
void OpenGLVertexArray::unbind() const
{
    HUAN_PROFILE_FUNCTION();
    glBindVertexArray(0);
    // HUAN_CORE_TRACE("OpenGL VertexArray unbinded, ID: {0}", myRendererID);
}
/**
 * @brief Set the VertexArray's Layout pointer with the VertexBuffer's Layout
 *
 * @param vertexBuffer
 */
void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    HUAN_PROFILE_FUNCTION();
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
        // glVertexAttribDivisor(myVertexBufferIndex, 1);
        myVertexBufferIndex++;
    }
    myVertexBuffers.push_back(vertexBuffer);
    HUAN_CORE_TRACE("OpenGL VertexArray {0} add VertexBuffer, ID: {1}", myRendererID, vertexBuffer->getMyRendererID());
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    HUAN_PROFILE_FUNCTION();
    myIndexBuffer = indexBuffer;
    HUAN_CORE_TRACE("OpenGL VertexArray, ID: {0} set IndexBuffer, ID: {1}", myRendererID,
                    indexBuffer->getMyRendererID());
}
constexpr uint32_t OpenGLVertexArray::getMyRendererID() const
{
    return myRendererID;
}
const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
{
    return myVertexBuffers;
}
const Ref<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
{
    return myIndexBuffer;
}
/**
 * @brief return the the first vb of va 's vertex number 
 * 
 * @return constexpr uint32_t 
 */
constexpr uint32_t OpenGLVertexArray::getVertexBufferCount() const
{
    HUAN_CORE_ASSERT((myVertexBuffers.size() == 1), "Get count function just could be used when there is only one vertexBuffer")
    return myVertexBuffers.begin()->get()->getMyVertexNumber();
}   
} // namespace Huan