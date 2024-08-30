#include "Sandbox.h"
#include "Renderer/RendererConfig.h"

Sandbox::Sandbox()
    : Huan::Layer("Sandbox"), myRenderer(Huan::Renderer::getInstance()), myCameraController(1280.0f / 720.0f)
{
}

void Sandbox::onAttach()
{
    HUAN_PROFILE_FUNCTION();

    myLogoTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/logo.png");
    myMetalTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/Metal/Metal_Color.png");
    myRenderer.loadPerspectiveCamera(myCameraController.getPerspectiveCamera());

    myLogoCuboidProperty = {.position = {0.0f, 0.0f, 0.0f},
                            .color = {1.0f, 1.0f, 1.0f, 1.0f},
                            .size = {1.0f, 1.0f, 1.0f},
                            .rotation = {0.0f, 0.0f, 0.0f},
                            .texture = myMetalTexture,
                            .tilingFactor = 1.0f};
}

void Sandbox::onDetach()
{
    HUAN_PROFILE_FUNCTION();
}

void Sandbox::onUpdate(Huan::TimeStep ts)
{
    // update
    myCameraController.onUpdate(ts);
    // render
    myRenderer.getRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    myRenderer.getRenderCommand()->clear();
    myRenderer.beginScene();
    for (int i = 0; i < 20; i++)
    {
        myLogoCuboidProperty.position.x = i - 10;
        for (int j = 0; j < 20; j++)
        {
            myLogoCuboidProperty.position.y = j - 10;
            myRenderer.drawCuboid(myLogoCuboidProperty);
        }
    }
    myRenderer.endScene();
}
void Sandbox::onImGuiRender()
{
    HUAN_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::SliderFloat3("Cuboid position", glm::value_ptr(myLogoCuboidProperty.position), -10.0f, 10.0f);
    ImGui::Text("Camera front: %f, %f, %f", myCameraController.getPerspectiveCamera()->getFront().x,
                myCameraController.getPerspectiveCamera()->getFront().y,
                myCameraController.getPerspectiveCamera()->getFront().z);
    ImGui::End();
}
void Sandbox::onEvent(Huan::Event& e)
{
    HUAN_PROFILE_FUNCTION();
    myCameraController.onEvent(e);
}