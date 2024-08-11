#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"
#include "Renderer/VertexArray.h"

namespace Huan
{

RenderCommand::RenderCommand()
{
    myRendererAPI = std::make_unique<CurrentRendererAPI>();
}

void RenderCommand::setClearColor(const glm::vec4& color)
{
    myRendererAPI->setClearColor(color);
}

void RenderCommand::clear()
{
    myRendererAPI->clear();
}

void RenderCommand::drawIndexed(const VertexArray& vertexArray)
{
    myRendererAPI->drawIndexed(vertexArray);
}

} // namespace Huan