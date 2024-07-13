#include "HuanPCH.h"
#include "Huan/Core.h"
#include "Huan/Application.h"
#include "Events/EventDispatcher.h"
#include "util/Log.h"


namespace Huan
{
	Application* Application::instance = nullptr;

	Application::Application(): myLayerStack()
	{
		HUAN_CORE_ASSERT(!instance, "Application already exists!")
		instance = this;
		Huan::Log::init();
		HUAN_CORE_INFO("Initialized Log! ");
		// create window
		myWindow = std::unique_ptr<Window>(Window::create());
		// use Application's onEvent as the window's callback func
		myWindow->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
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
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

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
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		myLayerStack.pushOverlay(layer);
		layer->onAttach();
	}

	Window& Application::getWindow()
	{ return *myWindow; }

	Application* Application::getInstance()
	{
		return instance;
	}
}
