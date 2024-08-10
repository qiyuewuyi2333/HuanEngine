#pragma once

#include "HuanPCH.h"
#include "Renderer/GraphicsContext.h"

namespace Huan
{
class OpenGLContext : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow* windowHandle);
    OpenGLContext(const OpenGLContext&) = delete;
    OpenGLContext(OpenGLContext&&) = delete;
    OpenGLContext& operator=(const OpenGLContext&) = delete;
    OpenGLContext& operator=(OpenGLContext&&) = delete;
    ~OpenGLContext();

  public:
    virtual void init() override;
    virtual void swapBuffers() override;

  private:
    GLFWwindow* myWindow = nullptr;
};
} // namespace Huan