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
    myRenderCommand->init();

    myData = new Renderer2DData();
    myData->quadTextureShader =
        std::make_shared<CurrentShader>("../../../../Assets/Shaders/flat_texture/flat_texture.vert",
                                        "../../../../Assets/Shaders/flat_texture/flat_texture.frag");
    // data
    float squareVertices[3 * 4] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    float squareTextureVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
                                          0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};
    // va vb ib
    myData->quadVertexArray = std::make_shared<CurrentVertexArray>();
    myData->quadVertexArray->bind();
    Ref<VertexBuffer> squareVB = std::make_shared<CurrentVertexBuffer>(squareVertices, sizeof(squareVertices));
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

    myData->myWhiteTexture = std::make_shared<Huan::CurrentTexture2D>(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    myData->myWhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
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

    myData->quadTextureShader->bind();
    myData->quadTextureShader->setMat4("u_ViewProjection", myData->camera->getViewProjectionMatrix());
}

void Renderer2D::renderScene()
{
    for (auto& va : myScene->getVertexArrays())
    {
        va->bind();
        myRenderCommand->drawIndexed(*va);
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
    myData->quadTextureShader->bind();
    myData->quadTextureShader->setVec4("u_Color", color.myColorValue);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    myData->quadTextureShader->setMat4("u_Transform", transform);
    myData->myWhiteTexture->bind();

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
    myData->quadTextureShader->setVec4("u_Color", glm::vec4(1.0f));
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