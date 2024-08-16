#pragma once
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
namespace Huan
{

class VertexArray
{
  public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
    virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

    virtual constexpr uint32_t getMyRendererID() const = 0;
};
} // namespace Huan