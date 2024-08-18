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

    // ��������а���������󶨸��������ö�Ӧ��uniform����
   /* if (myScene->getTexture() != nullptr)
    {
        myScene.getTexture()->bind();
        shader->setInt("u_Texture", 0);
    }*/

}

void Renderer2D::renderScene()
{
    // ���������е����ж������飬��ÿ���������������Ⱦ
    for (auto& va : myScene->getVertexArrays())
    {
        // �󶨶������飬�Ա����������Ķ�������
        va->bind();

        // ִ�л����������ġ����������ơ�����Ⱦ��������ؼ���һ������������ģ����θ��ݶ������ݻ��Ƶ���Ļ��

        myRenderCommand->drawIndexed(*va);

        // ��󶥵����飬����Ӱ���������
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