#include "Sandbox.h"
#include "Renderer/RendererConfig.h"

Sandbox::Sandbox()
    : Huan::Layer("Sandbox"), myRenderer(Huan::Renderer::getInstance()), myCameraController(1280.0f / 720.0f)
{
    const int n = 100;
    instancePositions.resize(n*n);
    for(int i = 0;i<n;++i)
    {
        for(int j = 0;j<n;++j)
            instancePositions[i*n+j] = glm::vec3(i - n/2, j - n/2, 0.0f);
    }

}

void Sandbox::onAttach()
{
    HUAN_PROFILE_FUNCTION();

    myLogoTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/logo.png");
    myMetalTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/Metal/Metal_Color.png");
    myRenderer.loadPerspectiveCamera(myCameraController.getPerspectiveCamera());

    myCuboidProperty = {    .position = {0.0f, 0.0f, 0.0f},
                            .color = {1.0f, 1.0f, 1.0f, 1.0f},
                            .size = {1.0f, 1.0f, 1.0f},
                            .rotation = {0.0f, 0.0f, 0.0f},
                            .texture = myMetalTexture,
                            .tilingFactor = 1.0f};
    // instanced
    const int n = 100;
    myCuboidProperties.resize(n*n, myCuboidProperty);
    for(int i = 0;i<n;++i)
    {
        for(int j = 0;j<n;++j)
            myCuboidProperties[i*n+j].position = glm::vec3(i - n/2, j - n/2, 0.0f);
    }
    myRenderer.drawCuboidInstanced(myCuboidProperties);
}

void Sandbox::onDetach()
{
    HUAN_PROFILE_FUNCTION();
}

void Sandbox::onUpdate(Huan::TimeStep ts)
{
    HUAN_PROFILE_FUNCTION();
    // update
    myCameraController.onUpdate(ts);
    // render
    myRenderer.getRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    myRenderer.getRenderCommand()->clear();
    myRenderer.beginScene();

    myRenderer.drawCuboid(myCuboidProperty);

    myRenderer.endScene();
}
void Sandbox::onImGuiRender()
{
    HUAN_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::SliderFloat3("Cuboid position", glm::value_ptr(myCuboidProperty.position), -10.0f, 10.0f);
    ImGui::Text("Camera front: %f, %f, %f", myCameraController.getPerspectiveCamera()->getFront().x,
                myCameraController.getPerspectiveCamera()->getFront().y,
                myCameraController.getPerspectiveCamera()->getFront().z);
    ImGui::SliderInt("cuboidNum: ", &cuboidNum, 1, 100);
    ImGui::End();
}
void Sandbox::onEvent(Huan::Event& e)
{
    HUAN_PROFILE_FUNCTION();
    myCameraController.onEvent(e);
}