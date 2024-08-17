#pragma once

#include "Huan/Core.h"
#include "Renderer/Utils/OrthogonalCamera.h"
#include "util/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Huan
{

class HUAN_API OrthogonalCameraController
{
  public:
    OrthogonalCameraController(float aspectRatio, bool rotation = false);

    void onUpdate(TimeStep ts);
    void onEvent(Event& e);
    Ref<Camera>& getCamera()
    {
        return myCamera;
    }
    const Ref<Camera>& getCamera() const
    {
        return myCamera;
    }

  private:
    bool onMouseScrolled(MouseScrolledEvent& e);
    bool onWindowResized(WindowResizeEvent& e);

  private:
    float myAspectRatio;
    float myZoomLevel = 1.0f;
    Ref<Camera> myCamera;

    bool myRotation;

    glm::vec3 myCameraPosition = {0.0f, 0.0f, 0.0f};
    float myCameraRotation = 0.0f;
    float myCameraTranslationSpeed = 5.0f, myCameraRotationSpeed = 180.0f;
};

} // namespace Huan
