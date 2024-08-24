#pragma once
#include "HuanPCH.h"
#include "Primitives/PrimitiveProperty.h"
#include "RenderCommand.h"
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
struct Renderer3DData
{
    // option
    bool myIsUsingMyPerspectiveCamera = true;
    // resource
    Ref<PerspectiveCamera> myPerspectiveCamera;
    Ref<OrthogonalCamera> myOrthogonalCamera;
    Ref<Shader> myCuboidTextureShader;
    Ref<VertexArray> myCuboidVertexArray;
    Ref<Texture> myWhiteTexture;

    const glm::mat4& getCameraMatrix()
    {
        return myIsUsingMyPerspectiveCamera ? myPerspectiveCamera->getProjectionViewMatrix() : myOrthogonalCamera->getViewProjectionMatrix();
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
    // primitives
    void drawCuboid(const CuboidProperty& cuboidProperty);
    // get
    const Scope<RenderCommand>& getRenderCommand() const;
  private:
    Scope<RenderCommand> myRenderCommand;
    // You might have many renderer to render one same scene
    Ref<Scene> myScene;
    Renderer3DData* myData;
};
} // namespace Huan