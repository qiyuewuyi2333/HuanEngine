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
    myScene->loadTexture("../../../../Assets/Textures/logo.png");

    myCheckboardTexture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/Checkerboard.png");
    myRenderer.loadScene(myScene);

    myQuad2D = std::make_shared<Huan::Quad2D>(Huan::Point2D{0.0f, 0.0f}, glm::vec2{1.0f, 1.0f},
                                              Huan::Color(1.0f, 0.834f, 0.0f, 0.3f));
    myQuad2DTex = std::make_shared<Huan::Quad2D>(Huan::Point2D{2.0f, 0.0f}, glm::vec2{1.0f, 1.0f},
                                                 Huan::Color(1.0f, 0.0f, 1.0f, 0.5f));
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
        myRenderer.drawQuad(glm::vec3(myQuad2DTex->myCenterPostion.x, myQuad2DTex->myCenterPostion.y, -0.1f),
                            myQuad2DTex->mySideLength * 10.0f, myCheckboardTexture);
        myRenderer.drawQuad(myQuad2D->myCenterPostion, myQuad2D->mySideLength, myQuad2D->myColor);
        // second render the transparent object
        myRenderer.drawQuad(myQuad2DTex->myCenterPostion, myQuad2DTex->mySideLength, myScene->getTexture());

        myRenderer.endScene();
    }
}

void Sandbox2D::onImGuiRender()
{
    HUAN_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(myQuad2D->myColor.myColorValue));
    ImGui::End();
}

void Sandbox2D::onEvent(Huan::Event& e)
{
    HUAN_PROFILE_FUNCTION();
    myCameraController.onEvent(e);
}
