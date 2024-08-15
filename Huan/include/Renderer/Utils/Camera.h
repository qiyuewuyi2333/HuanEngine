#pragma once

#include "HuanPCH.h"

namespace Huan
{
class Camera
{
  public:
    virtual void setProjectionMatrix(const glm::mat4& projectionMatrix) = 0;
    virtual void setPosition(const glm::vec3& position) = 0;
    virtual void setMyFront(const glm::vec3& front) = 0;
    virtual void setUp(const glm::vec3& up) = 0;
    virtual void setYaw(float yaw) = 0;
    virtual void setPitch(float pitch) = 0;

    virtual const glm::mat4& getViewMatrix() const = 0;
    virtual const glm::mat4& getProjectionMatrix() const = 0;
    virtual const glm::vec3& getPosition() const = 0;
    virtual const glm::mat4& getViewProjectionMatrix() const = 0;

    virtual void updateViewMatrix() = 0;
};
} // namespace Huan