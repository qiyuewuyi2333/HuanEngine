#include "HuanPCH.h"
#include "Platform/Windows/WindowsWindow.h"
#include "util/Log.h"


namespace Huan
{
	static bool sGLFWInitialized = false;

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
		if(!sGLFWInitialized)
		{
			int success = glfwInit();
			HUAN_CORE_ASSERT(success, "Could not initialize GLFW!");
			sGLFWInitialized = true;
		}
		myWindow = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), myData.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(myWindow);
		glfwSetWindowUserPointer(myWindow, &myData);
		setVSync(true);
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
		glfwSwapBuffers(myWindow);
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




}
