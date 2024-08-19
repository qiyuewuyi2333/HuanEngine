#include "Renderer/Utils/OrthogonalCamera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_common.hpp"

namespace Huan
{
OrthogonalCamera::OrthogonalCamera(float left, float right, float bottom, float top)
    : myProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), myViewMatrix(1.0f)
{
    myPosition = {0.0f, 0.0f, 0.0f};
    myRotate = 0.0f;
    myZoom = 1.0f;
    updateViewMatrix();
}
// OrthogonalCamera::OrthogonalCamera(float left, float right, float bottom, float top,
//                                    const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
//     : myPosition(position), myUp(up), myFront(glm::vec3(0.0f, 0.0f, -1.0f)), myYaw(yaw), myPitch(pitch)
// {
//     myProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
//     myViewMatrix = glm::lookAt(myPosition, myPosition + myFront, myUp);
// }
void OrthogonalCamera::setPosition(const glm::vec3& postion)
{
    myPosition = postion;
    updateViewMatrix();
}
void OrthogonalCamera::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
    myProjectionMatrix = projectionMatrix;
    updateViewMatrix();
}
 void OrthogonalCamera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    myProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    updateViewMatrix();
}

void OrthogonalCamera::setMyFront(const glm::vec3& front)
{
    myFront = front;
}
void OrthogonalCamera::setUp(const glm::vec3& up)
{
    myUp = up;
}
void OrthogonalCamera::setYaw(float yaw)
{
    myYaw = yaw;
}
void OrthogonalCamera::setPitch(float pitch)
{
    myPitch = pitch;
}
const glm::mat4& OrthogonalCamera::getProjectionMatrix() const
{
    return myProjectionMatrix;
}
const glm::mat4& OrthogonalCamera::getViewMatrix() const
{
    return myViewMatrix;
}
const glm::vec3& OrthogonalCamera::getPosition() const
{
    return myPosition;
}
const glm::mat4& OrthogonalCamera::getViewProjectionMatrix() const
{
    return myViewProjectionMatrix;
}
void OrthogonalCamera::updateViewMatrix()
{
    HUAN_PROFILE_FUNCTION();
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), myPosition) *
			glm::rotate(glm::mat4(1.0f), glm::radians(myRotate), glm::vec3(0, 0, 1));
    myViewMatrix = glm::inverse(transform);
    myViewProjectionMatrix = myProjectionMatrix * myZoom * myViewMatrix;
}
void OrthogonalCamera::move(const glm::vec3& move)
{
    myPosition += move * myCameraMoveSpeed;
    updateViewMatrix();
}
void OrthogonalCamera::rotate(float rotateValue)
{
    myRotate += rotateValue * myCameraRotateSpeed;
    updateViewMatrix();
}
 void OrthogonalCamera::zoom(float zoomValue)
 {
    myZoom += zoomValue * myCameraZoomSpeed;
    updateViewMatrix();
 }

const glm::vec3& OrthogonalCamera::getFront() const
{
    return myFront;
}

} // namespace Huan