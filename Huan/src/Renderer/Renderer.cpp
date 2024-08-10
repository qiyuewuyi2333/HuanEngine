#include "Renderer/Renderer.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
Renderer::Renderer()
{
    myRendererAPI = std::make_unique<CurrentRendererAPI>();
}

void Renderer::render(Shader& shader, Scene& scene)
{
    shader.use();
    scene.getVertexArray().bind();
    myRendererAPI->drawIndexed(scene.getVertexArray());
    scene.getVertexArray().unbind();
}
const std::unique_ptr<RendererAPI>& Renderer::getCurrentRendererAPI() const
{
    return myRendererAPI;
}

} // namespace Huan