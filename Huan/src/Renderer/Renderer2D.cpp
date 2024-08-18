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
    myRenderCommand = std::make_unique<RenderCommand>();

    myData = new Renderer2DData();
    myData->platSingleColorShader = std::make_shared<CurrentShader>("../../../../Assets/Shaders/flat/flat.vert",
                                                                        "../../../../Assets/Shaders/flat/flat.frag");
    myData->quadTextureShader = std::make_shared<CurrentShader>("../../../../Assets/Shaders/flat_texture/flat_texture.vert",
                                                                    "../../../../Assets/Shaders/flat_texture/flat_texture.frag");
    // data
    float squareVertices[3 * 4] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    float squareTextureVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
                                          0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};
    // va vb ib
    myData->quadVertexArray = std::make_shared<CurrentVertexArray>();
    myData->quadVertexArray->bind();
    Ref<VertexBuffer> squareVB =
        std::make_shared<CurrentVertexBuffer>(squareVertices, sizeof(squareVertices));
    squareVB->bind();
    BufferLayout squareLayout = {{ShaderDataType::Float3, "inVertice"}};
    squareVB->setLayout(squareLayout);
    Ref<IndexBuffer> squareIB = std::make_shared<CurrentIndexBuffer>(squareIndices, 6);
    squareIB->bind();
    myData->quadVertexArray->addVertexBuffer(squareVB);
    myData->quadVertexArray->setIndexBuffer(squareIB);

    // va vb ib
    myData->quadTextureVertexArray = std::make_shared<CurrentVertexArray>();
    myData->quadTextureVertexArray->bind();
    Ref<VertexBuffer> quadTextureVB =
        std::make_shared<CurrentVertexBuffer>(squareTextureVertices, sizeof(squareTextureVertices));
    quadTextureVB->bind();
    BufferLayout quadTextureLayout = {{ShaderDataType::Float3, "inVertice"},
                                      {ShaderDataType::Float2, "inTextureCoord"}};
    quadTextureVB->setLayout(quadTextureLayout);
    myData->quadTextureVertexArray->addVertexBuffer(quadTextureVB);
    squareIB->bind();
    myData->quadTextureVertexArray->setIndexBuffer(squareIB);

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
    myData->myTexture = myScene->getTexture();
}


void Renderer2D::beginScene()
{
    HUAN_CORE_ASSERT((myScene != nullptr), "The scene of Renderer2D hasn't been loaded!");

    myData->platSingleColorShader->bind();
    myData->platSingleColorShader->setMat4("u_ViewProjection", myData->camera->getViewProjectionMatrix());
    myData->quadTextureShader->bind();
    myData->quadTextureShader->setMat4("u_ViewProjection", myData->camera->getViewProjectionMatrix());
    

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

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture)
{
    drawQuad({position.x, position.y, 0.0f}, size, texture);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture)
{
    myData->quadTextureShader->bind();
    myData->quadTextureShader->setInt("u_Texture", 0);

    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    myData->quadTextureShader->setMat4("u_Transform", transform);
    texture->bind();

    myData->quadTextureVertexArray->bind();
    myRenderCommand->drawIndexed(*myData->quadTextureVertexArray);
}

const Scope<RenderCommand>& Renderer2D::getRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan