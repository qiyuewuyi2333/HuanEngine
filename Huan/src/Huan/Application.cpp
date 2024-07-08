#include "HuanPCH.h"

#include "Huan/Application.h"
#include "Events/EventDispatcher.h"
#include "util/Log.h"
#include <GLFW/glfw3.h>

namespace Huan
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application(): myLayerStack()
	{
		Huan::Log::init();
		HUAN_CORE_INFO("Initialized Log! ");

		myWindow = std::unique_ptr<Window>(Window::create());
		myWindow->setEventCallback(BIND_EVENT_FUNC(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		const WindowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategory::EventCategoryApplication))
		{
			HUAN_CLIENT_TRACE(e.toString());

			while (isRunning)
			{
				glClearColor(0, 1, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				for(Layer* layer : myLayerStack)
					layer->onUpdate();

				myWindow->onUpdate();
			}
		}

	}
	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(onWindowClose));

		for(auto it = myLayerStack.end(); it != myLayerStack.begin();)
		{
			--it;
			(*it)->onEvent(e);
			if(e.handled)
				break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}

	void Application::pushLayer(Layer* layer)
	{
		myLayerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		myLayerStack.pushOverlay(layer);
	}
}
