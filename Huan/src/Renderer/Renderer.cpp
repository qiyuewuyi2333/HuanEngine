#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
Renderer::Renderer()
{
    myRenderCommand = std::make_unique<RenderCommand>();
    myRenderCommand->init();
    init();
}
void Renderer::loadMaterial()
{
    Ref<Shader> myBaseMaterialShader =
        std::make_shared<CurrentShader>("../../../../Assets/Shaders/cube_texture/cube_texture.vert",
                                        "../../../../Assets/Shaders/cube_texture/cube_texture.frag");
    Ref<Texture> myWhiteTexture = std::make_shared<CurrentTexture2D>(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    myWhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

    myData->myBaseMaterial = std::make_shared<CurrentMaterial>("Base Material");
    myData->myBaseMaterial->setShader(myBaseMaterialShader);
    myData->myBaseMaterial->setTexture("Pure White", myWhiteTexture);

}

void Renderer::init()
{
    myData = new Renderer3DData();
    // Load camera
    // You don't need to create camera here, just move the power to
    // app layer, and load from it

    // load material
    loadMaterial();

    float cuboidVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
    // Create cube va, no ib
    myData->myCuboidVertexArray = std::make_shared<CurrentVertexArray>();
    myData->myCuboidVertexArray->bind();
    Ref<VertexBuffer> myCuboidVertexBuffer =
        std::make_shared<CurrentVertexBuffer>(cuboidVertices, sizeof(cuboidVertices));
    myCuboidVertexBuffer->bind();
    myCuboidVertexBuffer->setLayout({{ShaderDataType::Float3, "in_Position"}, {ShaderDataType::Float2, "in_TexCoord"}});
    myData->myCuboidVertexArray->addVertexBuffer(myCuboidVertexBuffer);
};
void Renderer::shutdown()
{
    delete myData;
}
void Renderer::loadOrthogonalCamera(Ref<OrthogonalCamera> camera)
{
    myData->myOrthogonalCamera = camera;
}
void Renderer::loadPerspectiveCamera(Ref<PerspectiveCamera> camera)
{
    myData->myPerspectiveCamera = camera;
}
void Renderer::beginScene()
{
}
void Renderer::renderScene()
{
    for (auto& va : myScene->getVertexArrays())
    {
        va->bind();
        myRenderCommand->drawIndexed(*va);
        va->unbind();
    }
}
void Renderer::endScene()
{
}
void Renderer::setScene(Ref<Scene> scene)
{
    myScene = scene;
}
void Renderer::drawCuboid(const CuboidProperty& property)
{
    myData->myBaseMaterial->bind();
    myData->myBaseMaterial->uploadUniformFloat4("u_Color", property.color);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), property.position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.z), {0.0f, 0.0f, 1.0f}) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.y), {0.0f, 1.0f, 0.0f}) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.x), {1.0f, 0.0f, 0.0f}) *
                          glm::scale(glm::mat4(1.0f), {property.size.x, property.size.y, property.size.z});
    glm::mat4 projectionView = myData->getCameraMatrix();

    myData->myBaseMaterial->uploadUniformMat4("u_ViewProjection", projectionView);
    myData->myBaseMaterial->uploadUniformMat4("u_Transform", transform);
    myData->myBaseMaterial->uploadUniformFloat("u_TilingFactor", property.tilingFactor);
    if (property.texture)
    {
        myData->myBaseMaterial->setTexture("Cuboid Texture", property.texture);
    }
    // twice bind
    myData->myBaseMaterial->bind();
    myData->myCuboidVertexArray->bind();
    myRenderCommand->draw(*myData->myCuboidVertexArray);
}
const Scope<RenderCommand>& Renderer::getRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan