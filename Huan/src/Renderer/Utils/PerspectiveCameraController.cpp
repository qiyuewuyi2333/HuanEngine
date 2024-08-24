#include "Renderer/Utils/PerspectiveCameraController.h"
#include "Events/EventDispatcher.h"
#include "Huan/KeyCodes.h"
#include "util/Input.h"

namespace Huan
{
PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float fov, float nearClip, float farClip)
    : myCamera(new PerspectiveCamera(aspectRatio, fov, nearClip, farClip)), myMoveSpeed(1.0f), myRotateSpeed(0.4f)
{
    
}

void PerspectiveCameraController::onUpdate(TimeStep ts)
{
    HUAN_PROFILE_FUNCTION();
    if (Input::isKeyPressed(HUAN_KEY_A))
    {
        myCamera->move(-myCamera->getRight() * ts.getSeconds() * myMoveSpeed);
    }
    else if (Input::isKeyPressed(HUAN_KEY_D))
    {
        myCamera->move(myCamera->getRight() * ts.getSeconds() * myMoveSpeed);
    }
    if (Input::isKeyPressed(HUAN_KEY_W))
    {
        myCamera->move(myCamera->getFront() * ts.getSeconds() * myMoveSpeed);
    }
    else if (Input::isKeyPressed(HUAN_KEY_S))
    {
        myCamera->move(-myCamera->getFront() * ts.getSeconds() * myMoveSpeed);
    }

    if (Input::isKeyPressed(HUAN_KEY_LEFT_ALT))
    {
        isCameraMode = true;
    }
    else if (Input::isKeyPressed(HUAN_KEY_ESCAPE))
    {
        isCameraMode = false;
    }
    if(isCameraMode)
    {
        Input::setCursorMode(1);
        float xOffset = Input::getMouseX() - myLastX;
        float yOffset = myLastY - Input::getMouseY();
        myLastX = Input::getMouseX();
        myLastY = Input::getMouseY();
        if (myFirstMouse)
        {
            xOffset = 0.0f;
            yOffset = 0.0f;
            myFirstMouse = false;
        }
        myCamera->rotate(xOffset * myRotateSpeed, yOffset * myRotateSpeed);
    }
    else
    {
        myFirstMouse = true;
        Input::setCursorMode(0);
    }
    
}
void PerspectiveCameraController::onEvent(Event& e)
{
    HUAN_PROFILE_FUNCTION();
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(PerspectiveCameraController::onMouseScrolled));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(PerspectiveCameraController::onWindowResized));
}

void PerspectiveCameraController::setPerspectiveCamera(Ref<PerspectiveCamera> camera)
{
    myCamera = camera;
}
Ref<PerspectiveCamera> PerspectiveCameraController::getPerspectiveCamera()
{
    return myCamera;
}

bool PerspectiveCameraController::onMouseScrolled(MouseScrolledEvent& event)
{

    return false;
}
bool PerspectiveCameraController::onWindowResized(WindowResizeEvent& event)
{
    myCamera->setAspectRatio(static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight()));
    return false;
}
} // namespace Huan