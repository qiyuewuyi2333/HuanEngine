#include "Platform/OpenGL/OpenGLContext.h"
#include "GLFW/glfw3.h"
#include "util/Log.h"
#include "Huan/Core.h"

namespace Huan
{
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : myWindow(windowHandle)
{
}

OpenGLContext::~OpenGLContext()
{
}

void OpenGLContext::init()
{
    glfwMakeContextCurrent(myWindow);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    HUAN_CORE_ASSERT(status, "Failed to initialize Glad!");

    HUAN_CORE_INFO("OpenGL Info:");
    HUAN_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
    HUAN_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
    HUAN_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));
}

void OpenGLContext::swapBuffers()
{
    glfwSwapBuffers(myWindow);
}
} // namespace Huan