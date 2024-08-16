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
    Huan::Scope<Huan::Scene> myScene1;
    Huan::Scope<Huan::Scene> myScene2;
    Huan::Scope<Huan::Scene> myScene3;
    Huan::Scope<Huan::Shader> shader;
    Huan::Ref<Huan::Camera> myCamera;
    Huan::Renderer& myRenderer;

};