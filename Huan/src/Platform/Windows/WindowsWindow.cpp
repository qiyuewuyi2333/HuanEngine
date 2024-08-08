#include "HuanPCH.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "util/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Huan
{
static bool sGLFWInitialized = false;
static void sGLFWErrorCallback(int error, const char* description)
{
    HUAN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}
Window* Window::create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    init(props);
}

void WindowsWindow::init(const WindowProps& props)
{
    myData.title = props.title;
    myData.width = props.width;
    myData.height = props.height;

    HUAN_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
    if (!sGLFWInitialized)
    {
        int success = glfwInit();
        HUAN_CORE_ASSERT(success, "Could not initialize GLFW!");
        glfwSetErrorCallback(sGLFWErrorCallback);
        sGLFWInitialized = true;
    }
    myWindow = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), myData.title.c_str(),
                                nullptr, nullptr);
    myContext = new OpenGLContext(myWindow);
    myContext->init();
    glfwSetWindowUserPointer(myWindow, &myData);
    setVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(myWindow, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(myWindow, [](GLFWwindow* window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.eventCallback(event);
    });

    glfwSetKeyCallback(myWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.eventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.eventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.eventCallback(event);
            break;
        }
        }
    });
    glfwSetCharCallback(myWindow, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.eventCallback(event);
    });
    glfwSetMouseButtonCallback(myWindow, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.eventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.eventCallback(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(myWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(myWindow, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        data.eventCallback(event);
    });
}

WindowsWindow::~WindowsWindow()
{
    WindowsWindow::shutdown();
}

void WindowsWindow::shutdown()
{
    glfwDestroyWindow(myWindow);
}

void WindowsWindow::onUpdate()
{
    glfwPollEvents();
    myContext->swapBuffers();
}

void* WindowsWindow::getNativeWindow() const
{
    return myWindow;
}

void WindowsWindow::setVSync(const bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
    myData.vSync = enabled;
}

bool WindowsWindow::isVSync() const
{
    return myData.vSync;
}
} // namespace Huan
