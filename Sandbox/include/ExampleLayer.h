#pragma once
#include "Layer/Layer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Scene.h"
#include "Renderer/Utils/Camera.h"
#include "util/TimeStep.h"


class ExampleLayer : public Huan::Layer
{
  public:
    ExampleLayer();
    ~ExampleLayer() = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(Huan::TimeStep timeStep) override;
    void onImGuiRender() override;
    void onEvent(Huan::Event& event) override;

  private:
    std::unique_ptr<Huan::Scene> myScene1;
    std::unique_ptr<Huan::Scene> myScene2;
    std::unique_ptr<Huan::Scene> myScene3;
    std::unique_ptr<Huan::Shader> shader;
    std::shared_ptr<Huan::Camera> myCamera;
    Huan::Renderer& myRenderer;

};