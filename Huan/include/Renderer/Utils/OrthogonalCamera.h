#pragma once

#include "Renderer/Utils/Camera.h"
#include "Huan/Core.h"
namespace Huan
{
class HUAN_API OrthogonalCamera : public Camera
{
  public:
    OrthogonalCamera(float left, float right, float bottom, float top);
    // OrthogonalCamera(float fov, float aspectRatio, float nearClip, float farClipconst,
    //                  const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
    //                  const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    virtual ~OrthogonalCamera() = default;

    virtual void setProjectionMatrix(const glm::mat4& projectionMatrix) override;
    virtual void setPosition(const glm::vec3& position) override;
    virtual void setMyFront(const glm::vec3& front) override;
    virtual void setUp(const glm::vec3& up) override;
    virtual void setYaw(float yaw) override;
    virtual void setPitch(float pitch) override;

    virtual const glm::mat4& getViewMatrix() const override;
    virtual const glm::mat4& getProjectionMatrix() const override;
    virtual const glm::vec3& getPosition() const override;
    virtual const glm::vec3& getFront() const override;
    virtual const glm::mat4& getViewProjectionMatrix() const override;

    virtual void updateViewMatrix() override;
    virtual void move(const glm::vec3& move = {0.0f, 0.0f, 0.0f}) override;
    virtual void rotate(float rotateValue) override;

  private:
    glm::mat4 myProjectionMatrix;
    glm::mat4 myViewMatrix;
    glm::mat4 myViewProjectionMatrix;
    glm::vec3 myPosition;
    glm::vec3 myUp;
    glm::vec3 myFront;
    float myRotate;
    float myYaw;
    float myPitch;

    float myCameraMoveSpeed = 1.0f;
    float myCameraRotateSpeed = 1.0f;
};
} // namespace Huan
