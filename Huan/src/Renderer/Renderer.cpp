#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
Renderer::Renderer()
{
    myRenderCommand = std::make_unique<RenderCommand>();
}

void Renderer::render(Shader& shader, Scene& scene)
{
    shader.use();
    scene.getVertexArray().bind();
    myRenderCommand->drawIndexed(scene.getVertexArray());
    scene.getVertexArray().unbind();
}
const std::unique_ptr<RenderCommand>& Renderer::getMyRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan