#pragma once

#include "glm/fwd.hpp"
#include "Huan/Core.h"

namespace Huan
{
class HUAN_API PerspectiveCamera
{
  public:
    PerspectiveCamera(float aspectRatio, float fov, float near, float far);
    ~PerspectiveCamera() = default;

    virtual void setPosition(const glm::vec3& position);
    virtual void setMyFront(const glm::vec3& front);
    virtual void setUp(const glm::vec3& up);
    virtual void setYaw(float yaw);
    virtual void setPitch(float pitch);
    virtual void setFov(float fov);
    virtual void setAspectRatio(float aspectRatio);
    virtual void setNear(float _near);
    virtual void setFar(float _far);

    virtual const glm::mat4& getViewMatrix() const;
    virtual const glm::mat4& getProjectionMatrix() const;
    virtual glm::mat4& getProjectionViewMatrix();
    virtual const glm::vec3& getPosition() const;
    virtual const glm::vec3& getFront() const;
    virtual const glm::vec3& getRight() const;

    virtual void move(const glm::vec3& move);
    virtual void rotate(const glm::vec3& rotateValue);
    virtual void rotate(float rotateX, float rotateY);
    virtual void zoom(float zoomValue);

  public:
    virtual void recalculateProjection();
    virtual void recalculateViewMatrix();
    virtual void recalculateVector();

  private:
    glm::mat4 myViewMatrix;
    glm::mat4 myProjectionMatrix;
    glm::mat4 myProjectionViewMatrix;
    glm::vec3 myPosition;
    glm::vec3 myFront;
    glm::vec3 myWorldUp;
    glm::vec3 myUp;
    glm::vec3 myRight;
    float myYaw;
    float myPitch;
    float myFov;
    float myAspectRatio;
    float myNear;
    float myFar;
};
} // namespace Huan