#include "Renderer/Renderer2D.h"

#include "Renderer/RendererConfig.h"

namespace Huan
{

Renderer2D::Renderer2D()
{
    init();
}

void Renderer2D::init()
{
    myRenderCommand = std::make_unique<Huan::RenderCommand>();

    myData = new Renderer2DData();
    myData->platSingleColorShader = std::make_shared<Huan::CurrentShader>("../../../../Assets/Shaders/flat/flat.vert",
                                                                          "../../../../Assets/Shaders/flat/flat.frag");

    // data
    float squareVertices[3 * 4] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    // va vb ib
    myData->quadVertexArray = std::make_shared<Huan::CurrentVertexArray>();
    myData->quadVertexArray->bind();
    Huan::Ref<Huan::VertexBuffer> squareVB =
        std::make_shared<Huan::CurrentVertexBuffer>(squareVertices, sizeof(squareVertices));
    squareVB->bind();
    Huan::BufferLayout squareLayout = {{Huan::ShaderDataType::Float3, "inVertice"}};
    squareVB->setLayout(squareLayout);
    Huan::Ref<Huan::IndexBuffer> squareIB = std::make_shared<Huan::CurrentIndexBuffer>(squareIndices, 6);
    squareIB->bind();
    myData->quadVertexArray->addVertexBuffer(squareVB);
    myData->quadVertexArray->setIndexBuffer(squareIB);
}

void Renderer2D::shutdown()
{
    delete myData;
}

/**
 * Load scene
 */
void Renderer2D::loadScene(Ref<Scene> scene)
{
    myScene = scene;
    myData->camera = myScene->getCamera();
}


void Renderer2D::beginScene()
{
    HUAN_CORE_ASSERT((myScene != nullptr), "The scene of Renderer2D hasn't been loaded!");

    myData->platSingleColorShader->bind();
    myData->platSingleColorShader->setMat4("u_ViewProjection", myData->camera->getViewProjectionMatrix());

    if (myScene->uColor != nullptr)
        myData->platSingleColorShader->setVec4("u_Color", *(myScene->uColor));

    // 如果场景中包含纹理，则绑定该纹理并设置对应的uniform变量
   /* if (myScene->getTexture() != nullptr)
    {
        myScene.getTexture()->bind();
        shader->setInt("u_Texture", 0);
    }*/

}

void Renderer2D::renderScene()
{
    // 遍历场景中的所有顶点数组，对每个顶点数组进行渲染
    for (auto& va : myScene->getVertexArrays())
    {
        // 绑定顶点数组，以便访问其包含的顶点数据
        va->bind();

        // 执行绘制命令，这里的“索引化绘制”是渲染过程中最关键的一环，它决定了模型如何根据顶点数据绘制到屏幕上

        myRenderCommand->drawIndexed(*va);

        // 解绑顶点数组，避免影响后续操作
        va->unbind();
    }
}

void Renderer2D::endScene()
{

}

void Renderer2D::setScene(Ref<Scene> scene)
{
    myScene = scene;
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color)
{
    drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Color& color)
{
    myData->platSingleColorShader->bind();
    myData->platSingleColorShader->setVec4("u_Color", color.myColorValue);
    myData->quadVertexArray->bind();
    myRenderCommand->drawIndexed(*myData->quadVertexArray);

}

const Scope<RenderCommand>& Renderer2D::getRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan