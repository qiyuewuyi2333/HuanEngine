#include "Sandbox2D.h"

#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Huan::Layer("Sandbox2D"),myRenderer(Huan::Renderer2D::getInstance()),
        myCameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::onAttach()
{
    // shader
    myScene = std::make_shared<Huan::Scene>(nullptr, myCameraController.getCamera());
    myScene->uColor = std::make_shared<glm::vec4>(1.0f);
    myRenderer.loadScene(myScene);
    myQuad2D =
        std::make_shared<Huan::Quad2D>(Huan::Point2D{0.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, Huan::Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Huan::TimeStep ts)
{
    // update
    myCameraController.onUpdate(ts);

    // render
    myRenderer.getRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    myRenderer.getRenderCommand()->clear();
    myRenderer.beginScene();
    myRenderer.drawQuad(myQuad2D->myCenterPostion, myQuad2D->mySideLength, myQuad2D->myColor);
    myRenderer.endScene();

}

void Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(myQuad2D->myColor.myColorValue));
    ImGui::End();
}

void Sandbox2D::onEvent(Huan::Event& e)
{
    myCameraController.onEvent(e);
}