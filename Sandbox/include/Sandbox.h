#pragma once

#include "Layer/Layer.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Primitives/PrimitiveProperty.h"
#include "Renderer/Renderer.h"
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "Renderer/Utils/PerspectiveCamera.h"
#include "Renderer/Utils/PerspectiveCameraController.h"

class Sandbox : public Huan::Layer
{
    
public:
	Sandbox();
	virtual ~Sandbox() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    void onUpdate(Huan::TimeStep ts) override;
    virtual void onImGuiRender() override;
    void onEvent(Huan::Event& e) override;

  private:
    Huan::Renderer& myRenderer;
    Huan::PerspectiveCameraController myCameraController;

    // Temp
    Huan::Ref<Huan::Scene> myScene;
    Huan::Ref<Huan::Shader> myFlatColorShader;
    Huan::Ref<Huan::Texture> myCheckboardTexture;
    Huan::Ref<Huan::Texture> myLogoTexture;

    Huan::CuboidProperty myLogoCuboidProperty;

};