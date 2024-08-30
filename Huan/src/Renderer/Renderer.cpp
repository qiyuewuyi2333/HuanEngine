#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
enum Topology
{
    Triangle = 0,
    Quad,
    Cuboid,
    Circle,
    Line,
    Point,
    Max
};

// int getTopology(Topology topology)
// {
//     switch (topology)
//     {
//     case Triangle:
//         return GL_TRIANGLES;
//     case Quad:
//         return GL_QUADS;
//     case Cuboid:
//         return GL_TRIANGLES;
//     case Circle:
//         return GL_TRIANGLES;
//     case Line:
//         return GL_LINES;
//     case Point:
//         return GL_POINTS;
//     default:
//         return GL_TRIANGLES;
//     }
//     return GL_TRIANGLES;
// }

Renderer::Renderer()
{
    myRenderCommand = std::make_unique<RenderCommand>();
    myRenderCommand->init();
    init();
}
void Renderer::loadMaterial()
{
    Ref<Shader> myBaseMaterialShader =
        std::make_shared<CurrentShader>(myData->cuboidVertShader, myData->metalFragShader);

    Ref<Texture> myWhiteTexture = std::make_shared<CurrentTexture2D>(1, 1);

    uint32_t whiteTextureData = 0xffffffff;
    myWhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

    myData->myBaseMaterial = std::make_shared<CurrentMaterial>("Base Material");
    myData->myBaseMaterial->setShader(myBaseMaterialShader);
    myData->myBaseMaterial->setTexture("Pure White", myWhiteTexture);
}
void Renderer::loadSingleShader()
{
    myData->cuboidVertShader =
        std::make_shared<CurrentShader>("../../../../Assets/Shaders/cube_texture/cube_texture.vert");
    myData->metalFragShader = std::make_shared<CurrentShader>("../../../../Assets/Shaders/metal/metal.frag");
}

void Renderer::init()
{
    HUAN_PROFILE_FUNCTION();
    myData = new Renderer3DData();
    // You don't need to create camera here, just move the power to
    // app layer, and load from it

    // load shader
    loadSingleShader();
    // load material
    loadMaterial();
    // clang-format off
    cuboidVertices = 
    {
        // positions          // normals           // texture coords   // color
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f,1.0f};

    // clang-format on
    myData->myBatchRenderData = std::make_shared<BatchRenderData>();

    myData->myBatchRenderData->vertexArray = std::make_shared<CurrentVertexArray>();
    myData->myBatchRenderData->vertexArray->bind();
    myData->myBatchRenderData->vertexBuffer =
        std::make_shared<CurrentVertexBuffer>(BatchRenderData::maxVertexNum * sizeof(float) * 12);
    myData->myBatchRenderData->vertexBuffer->bind();
    myData->myBatchRenderData->vertexBuffer->setLayout({{ShaderDataType::Float3, "in_Position"},
                                                        {ShaderDataType::Float3, "in_Normal"},
                                                        {ShaderDataType::Float2, "in_TexCoord"},
                                                        {ShaderDataType::Float4, "in_Color"}});
    myData->myBatchRenderData->vertexArray->addVertexBuffer(myData->myBatchRenderData->vertexBuffer);
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
    flush();
}
void Renderer::setScene(Ref<Scene> scene)
{
    myScene = scene;
}
void Renderer::drawCuboid(const CuboidProperty& property)
{
    HUAN_PROFILE_FUNCTION();
    if (myData->instanceCount >= BatchRenderData::maxInstanceNum)
        flush();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), property.position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.z), {0.0f, 0.0f, 1.0f}) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.y), {0.0f, 1.0f, 0.0f}) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(property.rotation.x), {1.0f, 0.0f, 0.0f}) *
                          glm::scale(glm::mat4(1.0f), {property.size.x, property.size.y, property.size.z});

    unsigned int stride = 12;
    for (int i = 0; i < 36; ++i)
    {
        glm::vec4 position = transform * glm::vec4(cuboidVertices[i * stride + 0], cuboidVertices[i * stride + 1],
                                                   cuboidVertices[i * stride + 2], 1.0f);

        // Pos
        myData->myBatchRenderData->vertexBufferData.push_back(position.x); 
        myData->myBatchRenderData->vertexBufferData.push_back(position.y);
        myData->myBatchRenderData->vertexBufferData.push_back(position.z);
        // Normal
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 3]);
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 4]);
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 5]);
        // TexC
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 6]); 
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 7]);

        // Color
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 8]);
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 9]);
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 10]);
        myData->myBatchRenderData->vertexBufferData.push_back(cuboidVertices[i * stride + 11]);
    }
    myData->vertexCount += 36;

    if (property.texture)
    {
        myData->myBaseMaterial->setTexture("Cuboid Texture", property.texture);
    }
}

void Renderer::flush() const
{
    HUAN_PROFILE_FUNCTION();
    // no Instance in the batch
    if (myData->vertexCount == 0)
        return;
    // upload data
    myData->myBatchRenderData->vertexArray->bind();
    myData->myBatchRenderData->vertexBuffer->bind();
    myData->myBatchRenderData->vertexBuffer->setData(myData->myBatchRenderData->vertexBufferData.data(),
                                                     myData->myBatchRenderData->vertexBufferData.size() *
                                                         sizeof(float));

    // bind material
    myData->myBaseMaterial->bind();
    myData->myBaseMaterial->uploadUniformMat4("u_ProjectionView", myData->getCameraMatrix());
    myData->myBaseMaterial->uploadUniformFloat("u_TilingFactor", myData->tilingFactor);

    myData->myBatchRenderData->vertexArray->bind();
    myRenderCommand->draw(*myData->myBatchRenderData->vertexArray);

    myData->myBatchRenderData->vertexBufferData.clear();
    myData->instanceCount = 0;
    myData->vertexCount = 0;
    myData->indexCount = 0;
}
const Scope<RenderCommand>& Renderer::getRenderCommand() const
{
    return myRenderCommand;
}

} // namespace Huan