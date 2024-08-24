#pragma once
#include "Renderer/VertexArray.h"
namespace Huan
{
class HUAN_API OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();

    ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;
    virtual const Ref<IndexBuffer>& getIndexBuffer() const override;
    virtual constexpr uint32_t getMyRendererID() const override;
    virtual constexpr uint32_t getVertexBufferCount() const override;

  private:
    uint32_t myRendererID;
    std::vector<Ref<VertexBuffer>> myVertexBuffers;
    Ref<IndexBuffer> myIndexBuffer;
    uint32_t myVertexBufferIndex = 0;
    
};
} // namespace Huan