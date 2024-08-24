#include "Huan/Application.h"
#include "Huan/Window.h"
#include "platform/Windows/windowsInput.h"

namespace Huan
{
	Input* Input::instance = new WindowsInput();
	WindowsInput::WindowsInput()
	{
		instance = this;
	}

	bool WindowsInput::isKeyPressedImpl(int keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::getMouseXImpl() const
	{
		auto [x, y] = getMousePositionImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl() const
	{
		auto [x, y] = getMousePositionImpl();
		return y;
	}
    void WindowsInput::setCursorModeImpl(uint32_t mode)
    {
        switch (mode)
        {
        case 0:
            glfwSetInputMode(static_cast<GLFWwindow*>(Application::getInstance()->getWindow().getNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case 1:
            glfwSetInputMode(static_cast<GLFWwindow*>(Application::getInstance()->getWindow().getNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        default:
            break;
        }
    }

}
