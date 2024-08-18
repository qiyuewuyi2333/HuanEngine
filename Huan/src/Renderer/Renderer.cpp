#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
Renderer::Renderer()
{
    myRenderCommand = std::make_unique<RenderCommand>();
}
void Renderer::init()
{
    myRenderCommand->init();
}

// 渲染函数，用于将场景中的顶点数据通过着色器渲染到屏幕上
void Renderer::render(Ref<Shader>& shader, Scene& scene)
{
    // 绑定着色器，以便使用其渲染逻辑
    shader->bind();

    // 设置视图投影矩阵，这是渲染计算中必不可少的一步，用于将场景中的物体转换到屏幕坐标上
}

const Scope<RenderCommand>& Renderer::getMyRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan