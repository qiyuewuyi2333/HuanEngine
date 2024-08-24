#pragma once

#include "Huan/Core.h"
#include "util/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Renderer/Utils/PerspectiveCamera.h"

namespace Huan
{
    
class HUAN_API PerspectiveCameraController
{
  public:
    PerspectiveCameraController(float aspectRatio, float fov = 45.0f, float near = 0.1f, float far = 1000.0f);
    ~PerspectiveCameraController() = default;

    void onUpdate(TimeStep ts);
    void onEvent(Event& event);
    void setPerspectiveCamera(Ref<PerspectiveCamera> camera);
    Ref<PerspectiveCamera> getPerspectiveCamera();

  private:
    bool onMouseScrolled(MouseScrolledEvent& event);
    bool onWindowResized(WindowResizeEvent& event);

  private:
    Ref<PerspectiveCamera> myCamera;
    float myMoveSpeed;
    float myRotateSpeed;
    float myZoomSpeed;
    float myLastX;
    float myLastY;
    bool myFirstMouse = true;
    bool isCameraMode = false;
};
} // namespace Huan