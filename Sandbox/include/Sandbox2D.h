#pragma once
#include "Layer/Layer.h"
#include "Renderer/Renderer2D.h"
#include "util/TimeStep.h"
#include "Renderer/RendererConfig.h"
#include "Renderer/Primitives/Quad2D.h"
#include "Renderer/Utils/OrthogonalCameraController.h"

class Sandbox2D : public Huan::Layer
{
  public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    void onUpdate(Huan::TimeStep ts) override;
    virtual void onImGuiRender() override;
    void onEvent(Huan::Event& e) override;

  private:
    Huan::Renderer2D& myRenderer;
    Huan::OrthogonalCameraController myCameraController;

    // Temp
    Huan::Ref<Huan::Scene> myScene;
    Huan::Ref<Huan::Shader> myFlatColorShader;
    Huan::Ref<Huan::Quad2D> myQuad2D;
    Huan::Ref<Huan::Quad2D> myQuad2DTex;
    Huan::Ref<Huan::Texture> myCheckboardTexture;

};
