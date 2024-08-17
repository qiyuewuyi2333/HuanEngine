#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Huan/Core.h"
#include "Events/EventDispatcher.h"
#include "Renderer/Utils/OrthogonalCamera.h"
#include "Renderer/Utils/OrthogonalCameraController.h"
#include "util/Input.h"
#include "Huan/KeyCodes.h"

namespace Huan
{
OrthogonalCameraController::OrthogonalCameraController(float aspectRatio, bool rotation )
    : myAspectRatio(aspectRatio),
      myCamera(new OrthogonalCamera(-myAspectRatio * myZoomLevel, myAspectRatio * myZoomLevel, -myZoomLevel, myZoomLevel)),
      myRotation(rotation)
{
}

void OrthogonalCameraController::onUpdate(TimeStep timeStep)
{
    if (Huan::Input::isKeyPressed(HUAN_KEY_LEFT))
        myCamera->move({-timeStep, 0.0f, 0.0f});
    else if (Huan::Input::isKeyPressed(HUAN_KEY_RIGHT))
        myCamera->move({timeStep, 0.0f, 0.0f});

    if (Huan::Input::isKeyPressed(HUAN_KEY_UP))
        myCamera->move({0.0f, timeStep, 0.0f});
    else if (Huan::Input::isKeyPressed(HUAN_KEY_DOWN))
        myCamera->move({0.0f, -timeStep, 0.0f});

    if (Huan::Input::isKeyPressed(HUAN_KEY_A))
        myCamera->rotate(timeStep);
    else if (Huan::Input::isKeyPressed(HUAN_KEY_D))
        myCamera->rotate(-timeStep);
}

void OrthogonalCameraController::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(OrthogonalCameraController::onMouseScrolled));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OrthogonalCameraController::onWindowResized));
}
bool OrthogonalCameraController::onMouseScrolled(MouseScrolledEvent& e)
{
    myZoomLevel -= e.getYOffset() * 0.25f;
    myZoomLevel = max(myZoomLevel, 0.25f);
    myCamera->setProjectionMatrix(-myAspectRatio * myZoomLevel, myAspectRatio * myZoomLevel, -myZoomLevel, myZoomLevel);
    return false;
}
bool OrthogonalCameraController::onWindowResized(WindowResizeEvent& e)
{
    myAspectRatio = (float)e.getWidth() / (float)e.getHeight();
    myCamera->setProjectionMatrix(-myAspectRatio * myZoomLevel, myAspectRatio * myZoomLevel, -myZoomLevel, myZoomLevel);
    return false;
}


} // namespace Huan
