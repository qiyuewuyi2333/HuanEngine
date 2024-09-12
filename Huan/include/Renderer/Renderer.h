#pragma once
#include "HuanPCH.h"
#include "Primitives/PrimitiveProperty.h"
#include "RenderCommand.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Shader.h"
#include "Renderer/Scene.h"
#include "Renderer/Utils/PerspectiveCamera.h"
#include "Renderer/Utils/OrthogonalCamera.h"

namespace Huan
{
enum RendererAPIName
{
    None,
    OpenGL,
    Vulkan
};

struct BatchRenderData
{
    static const unsigned int maxInstanceNum = 10000;
    static const unsigned int maxVertexNum = 10000 * 6 * 6;
    static const unsigned int maxIndexNum = 10000 * 6 * 6;

    Ref<VertexArray> vertexArray;
    Ref<VertexBuffer> vertexBuffer;

    std::vector<float> vertexBufferData;
    std::vector<unsigned int> indices;

    unsigned int instanceCount = 0;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
};
struct RendererProperty
{
    // option
    bool myIsUsingMyPerspectiveCamera = true;
    // resource
    Ref<PerspectiveCamera> myPerspectiveCamera;
    Ref<OrthogonalCamera> myOrthogonalCamera;
    Ref<Shader> cuboidVertShader;
    Ref<Shader> metalFragShader;
    Ref<Material> myBaseMaterial;
    Ref<Material> myMetalMaterial;

    float tilingFactor = 1.0f;

    // Batch Rendering
    Ref<BatchRenderData> myBatchInstanceData;

    // TODO: myBatchRenderData modify to myBatchNormalData
    Ref<BatchRenderData> myBatchRenderData;

    const glm::mat4& getCameraMatrix()
    {
        return myIsUsingMyPerspectiveCamera ? myPerspectiveCamera->getProjectionViewMatrix()
                                            : myOrthogonalCamera->getViewProjectionMatrix();
    }
};
class HUAN_API Renderer
{
  public:
    static Renderer& getInstance()
    {
        static Renderer instance;
        return instance;
    }

    Renderer();
    Renderer(const Renderer&) = delete;

    void init();

    void shutdown();

    void loadScene(Ref<Scene> scene);
    void loadOrthogonalCamera(Ref<OrthogonalCamera> camera);
    void loadPerspectiveCamera(Ref<PerspectiveCamera> camera);
    void beginScene();
    void renderScene();
    void endScene();
    void setScene(Ref<Scene> scene);

    void flushNormal() const;
    void flushInstanced() const;
    // primitives
    void drawCuboid(const CuboidProperty& cuboidProperty);
    void drawCuboidInstanced(const std::vector<CuboidProperty>& cuboidProperty);
    // get
    const Scope<RenderCommand>& getRenderCommand() const;

  private:
    void loadMaterial();
    void loadSingleShader();

  private:
    Scope<RenderCommand> myRenderCommand;
    // You might have many renderer to render one same scene
    Ref<Scene> myScene;
    RendererProperty* myData;
    std::array<float, 36 * 12> cuboidVertices;
};
} // namespace Huan