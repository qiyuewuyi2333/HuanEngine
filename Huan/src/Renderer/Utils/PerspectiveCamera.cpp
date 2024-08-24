#include "Renderer/Utils/PerspectiveCamera.h"

namespace Huan
{

// glm::mat4 myViewMatrix;
// glm::mat4 myProjectionMatrix;
// glm::mat4 myViewProjectionMatrix;
// glm::vec3 myPosition;
// glm::vec3 myRotation;
// glm::vec3 myFront;
// glm::vec3 myUp;
// glm::vec3 myRight;
// glm::vec3 myWorldUp;
PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fov, float nearClip, float farClip)
    : myPosition(0.0f, 0.0f, -10.0f), myFront(0.0f, 0.0f, -1.0f), myWorldUp(0.0f, 1.0f, 0.0f), myUp(myWorldUp),
      myRight(glm::normalize(glm::cross(myFront, myUp))), myYaw(90.0f), myPitch(0.0f), myFov(fov),
      myAspectRatio(aspectRatio), myNear(nearClip), myFar(farClip)
{
    HUAN_PROFILE_FUNCTION();
    recalculateVector();
    recalculateProjection();
    recalculateViewMatrix();
}

void PerspectiveCamera::setPosition(const glm::vec3& position)
{
    myPosition = position;
    recalculateViewMatrix();
}
void PerspectiveCamera::setMyFront(const glm::vec3& front)
{
    myFront = front;
    recalculateViewMatrix();
}
void PerspectiveCamera::setUp(const glm::vec3& up)
{
    myUp = up;
    recalculateViewMatrix();
}
void PerspectiveCamera::setYaw(float yaw)
{
    myYaw = yaw;
    recalculateViewMatrix();
}
void PerspectiveCamera::setPitch(float pitch)
{
    myPitch = pitch;
    recalculateViewMatrix();
}
void PerspectiveCamera::setFov(float fov)
{
    myFov = fov;
    recalculateProjection();
}
void PerspectiveCamera::setAspectRatio(float aspectRatio)
{
    myAspectRatio = aspectRatio;
    recalculateProjection();
}
void PerspectiveCamera::setNear(float _near)
{
    myNear = _near;
    recalculateProjection();
}
void PerspectiveCamera::setFar(float _far)
{
    myFar = _far;
    recalculateProjection();
}

const glm::mat4& PerspectiveCamera::getViewMatrix() const
{
    return myViewMatrix;
}
const glm::mat4& PerspectiveCamera::getProjectionMatrix() const
{
    return myProjectionMatrix;
}
glm::mat4& PerspectiveCamera::getProjectionViewMatrix()
{
    HUAN_PROFILE_FUNCTION();
    myProjectionViewMatrix = myProjectionMatrix * myViewMatrix;
    return myProjectionViewMatrix;
}
const glm::vec3& PerspectiveCamera::getPosition() const
{
    return myPosition;
    
}
const glm::vec3& PerspectiveCamera::getFront() const
{
    return myFront;
}
const glm::vec3& PerspectiveCamera::getRight() const
{
    return myRight;
}

void PerspectiveCamera::move(const glm::vec3& move)
{
    HUAN_PROFILE_FUNCTION();
    myPosition += move;
    recalculateViewMatrix();
}
void PerspectiveCamera::rotate(const glm::vec3& rotateValue)
{
    HUAN_PROFILE_FUNCTION();
    myYaw += rotateValue.x;
    myPitch += rotateValue.y;
    myPitch = glm::clamp(myPitch, -89.0f, 89.0f);
    recalculateVector();
    recalculateViewMatrix();
}
void PerspectiveCamera::rotate(float rotateX, float rotateY)
{
    HUAN_PROFILE_FUNCTION();
    myYaw += rotateX;
    myPitch += rotateY;
    myPitch = glm::clamp(myPitch, -89.0f, 89.0f);
    recalculateVector();
    recalculateViewMatrix();
}
void PerspectiveCamera::zoom(float zoomValue)
{
    myFov -= zoomValue;
    recalculateProjection();
}
void PerspectiveCamera::recalculateProjection()
{
    HUAN_PROFILE_FUNCTION();
    myProjectionMatrix = glm::perspective(glm::radians(myFov), myAspectRatio, myNear, myFar);
}
void PerspectiveCamera::recalculateViewMatrix()
{
    HUAN_PROFILE_FUNCTION();
    myViewMatrix = glm::lookAt(myPosition, myPosition + myFront, myUp);
}
void PerspectiveCamera::recalculateVector()
{
    myFront = glm::normalize(glm::vec3(glm::cos(glm::radians(myYaw)) * glm::cos(glm::radians(myPitch)),
                                       glm::sin(glm::radians(myPitch)),
                                       glm::sin(glm::radians(myYaw)) * glm::cos(glm::radians(myPitch))));
    myRight = glm::normalize(glm::cross(myFront, myWorldUp));
    myUp = glm::normalize(glm::cross(myRight, myFront));
}

} // namespace Huan