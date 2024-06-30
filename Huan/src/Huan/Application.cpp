#include "HuanPCH.h"

#include "Huan/Application.h"
#include "Events/ApplicationEvent.h"
#include "util/Log.h"

#include <GLFW/glfw3.h>

namespace Huan
{
	Application::Application()
	{
		Huan::Log::init();
		HUAN_CORE_INFO("Initialized Log! ");

		myWindow = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
	}

	void Application::run() 
	{
		const WindowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategory::EventCategoryApplication))
		{
			while (isRunning)
			{
				HUAN_CLIENT_TRACE(e.toString());
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				myWindow->onUpdate();
			}
		}
		if (e.isInCategory(EventCategory::EventCategoryInput))
		{
			HUAN_CLIENT_TRACE(e.toString());
		}

	}
	
}
