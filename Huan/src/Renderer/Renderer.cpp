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
    shader.setMat4("u_ViewProjection", scene.getCamera()->getViewProjectionMatrix());
    for(auto& va :scene.getVertexArrays())
    {
        va->bind();
        myRenderCommand->drawIndexed(*va);
        va->unbind();
    }
}
const std::unique_ptr<RenderCommand>& Renderer::getMyRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan