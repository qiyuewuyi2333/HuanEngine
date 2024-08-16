#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
Renderer::Renderer()
{
    myRenderCommand = std::make_unique<RenderCommand>();
}


// 渲染函数，用于将场景中的顶点数据通过着色器渲染到屏幕上
void Renderer::render(Ref<Shader>& shader, Scene& scene)
{
    // 绑定着色器，以便使用其渲染逻辑
    shader->bind();
    
    // 设置视图投影矩阵，这是渲染计算中必不可少的一步，用于将场景中的物体转换到屏幕坐标上
    shader->setMat4("u_ViewProjection", scene.getCamera()->getViewProjectionMatrix());
    
    // 如果场景中包含纹理，则绑定该纹理并设置对应的uniform变量
    if(scene.getTexture() != nullptr)
    {
        scene.getTexture()->bind(); 
        shader->setInt("u_Texture", 0);
    }
    
    // 遍历场景中的所有顶点数组，对每个顶点数组进行渲染
    for(auto& va :scene.getVertexArrays())
    {
        // 绑定顶点数组，以便访问其包含的顶点数据
        va->bind();
        
        // 执行绘制命令，这里的“索引化绘制”是渲染过程中最关键的一环，它决定了模型如何根据顶点数据绘制到屏幕上
        myRenderCommand->drawIndexed(*va);
        
        // 解绑顶点数组，避免影响后续操作
        va->unbind();
    }
}

const Scope<RenderCommand>& Renderer::getMyRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan