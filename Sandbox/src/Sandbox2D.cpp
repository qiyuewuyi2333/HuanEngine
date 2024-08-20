#include "Sandbox2D.h"
#include "HuanPCH.h"

Sandbox2D::Sandbox2D()
    : Huan::Layer("Sandbox2D"), myRenderer(Huan::Renderer2D::getInstance()), myCameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::onAttach()
{
    HUAN_PROFILE_FUNCTION();

    // shader
    myScene = std::make_shared<Huan::Scene>(nullptr, myCameraController.getCamera());
    myScene->uColor = std::make_shared<glm::vec4>(1.0f);
    // myScene->loadTexture("../../../../Assets/Textures/logo.png");

    // texture
    myCheckboardTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/Checkerboard.png");
    myLogoTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/logo.png");

    // camera
    myRenderer.loadCamera(myCameraController.getCamera());


    myCheckboard = {.position = {0.0f,0.0f,-0.1f},
                    .color = {1.0f, 1.0f, 1.0f, 1.0f},
                    .size = {10.0f, 10.0f},
                    .rotation = {0.0f, 0.0f, 0.0f},
                    .texture = myCheckboardTexture,
                    .tilingFactor = 10.0f};

    myColorQuad =  {.position = {-2.0f,0.0f, 0.0f},
                    .color = {1.0f, 0.834f, 0.0f, 0.3f},
                    .size = {1.0f, 1.0f},
                    .rotation = {0.0f, 0.0f, 0.0f},
                    .texture = nullptr,
                    .tilingFactor = 1.0f};

    myLogoQuad =  {.position = {2.0f,0.0f, 0.0f},
                    .color = {1.0f, 1.0f, 1.0f, 1.0f},
                    .size = {1.0f, 1.0f},
                    .rotation = {0.0f, 0.0f, 0.0f},
                    .texture = myLogoTexture,
                    .tilingFactor = 1.0f};
}

void Sandbox2D::onDetach()
{
    HUAN_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(Huan::TimeStep ts)
{
    HUAN_PROFILE_FUNCTION();
    // update
    {
        HUAN_PROFILE_SCOPE("CameraController::onUpdate");
        myCameraController.onUpdate(ts);
    }
    {
        HUAN_PROFILE_SCOPE("Sandbox::render");
        // render
        myRenderer.getRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        myRenderer.getRenderCommand()->clear();
        myRenderer.beginScene();
        // first render the opaque object
        myRenderer.drawQuad(myCheckboard);
        myRenderer.drawQuad(myColorQuad);
        // second render the transparent object
        myRenderer.drawQuad(myLogoQuad);

        myRenderer.endScene();
    }
}

void Sandbox2D::onImGuiRender()
{
    HUAN_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(myColorQuad.color));
    ImGui::End();
}

void Sandbox2D::onEvent(Huan::Event& e)
{
    HUAN_PROFILE_FUNCTION();
    myCameraController.onEvent(e);
}
