#pragma once
#include "Renderer/VertexArray.h"
namespace Huan
{
class OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();

    ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;

    virtual constexpr uint32_t getMyRendererID() const override;

  private:
    uint32_t myRendererID;
    std::vector<std::shared_ptr<VertexBuffer>> myVertexBuffers;
    std::shared_ptr<IndexBuffer> myIndexBuffer;
    uint32_t myVertexBufferIndex = 0;
    
};
} // namespace Huan