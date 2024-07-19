#include "HuanPCH.h"
#include "Huan/Core.h"
#include "Huan/Application.h"
#include "Events/EventDispatcher.h"
#include "util/Log.h"
#include "Huan/KeyCodes.h"



namespace Huan
{
	std::unordered_map<int, std::string> createKeycodeMap() {
		std::unordered_map<int, std::string> keycodeMap;

		keycodeMap[HUAN_KEY_SPACE] = "HUAN_KEY_SPACE";
		keycodeMap[HUAN_KEY_APOSTROPHE] = "HUAN_KEY_APOSTROPHE";
		keycodeMap[HUAN_KEY_COMMA] = "HUAN_KEY_COMMA";
		keycodeMap[HUAN_KEY_MINUS] = "HUAN_KEY_MINUS";
		keycodeMap[HUAN_KEY_PERIOD] = "HUAN_KEY_PERIOD";
		keycodeMap[HUAN_KEY_SLASH] = "HUAN_KEY_SLASH";
		keycodeMap[HUAN_KEY_0] = "HUAN_KEY_0";
		keycodeMap[HUAN_KEY_1] = "HUAN_KEY_1";
		keycodeMap[HUAN_KEY_2] = "HUAN_KEY_2";
		keycodeMap[HUAN_KEY_3] = "HUAN_KEY_3";
		keycodeMap[HUAN_KEY_4] = "HUAN_KEY_4";
		keycodeMap[HUAN_KEY_5] = "HUAN_KEY_5";
		keycodeMap[HUAN_KEY_6] = "HUAN_KEY_6";
		keycodeMap[HUAN_KEY_7] = "HUAN_KEY_7";
		keycodeMap[HUAN_KEY_8] = "HUAN_KEY_8";
		keycodeMap[HUAN_KEY_9] = "HUAN_KEY_9";
		keycodeMap[HUAN_KEY_SEMICOLON] = "HUAN_KEY_SEMICOLON";
		keycodeMap[HUAN_KEY_EQUAL] = "HUAN_KEY_EQUAL";
		keycodeMap[HUAN_KEY_A] = "HUAN_KEY_A";
		keycodeMap[HUAN_KEY_B] = "HUAN_KEY_B";
		keycodeMap[HUAN_KEY_C] = "HUAN_KEY_C";
		keycodeMap[HUAN_KEY_D] = "HUAN_KEY_D";
		keycodeMap[HUAN_KEY_E] = "HUAN_KEY_E";
		keycodeMap[HUAN_KEY_F] = "HUAN_KEY_F";
		keycodeMap[HUAN_KEY_G] = "HUAN_KEY_G";
		keycodeMap[HUAN_KEY_H] = "HUAN_KEY_H";
		keycodeMap[HUAN_KEY_I] = "HUAN_KEY_I";
		keycodeMap[HUAN_KEY_J] = "HUAN_KEY_J";
		keycodeMap[HUAN_KEY_K] = "HUAN_KEY_K";
		keycodeMap[HUAN_KEY_L] = "HUAN_KEY_L";
		keycodeMap[HUAN_KEY_M] = "HUAN_KEY_M";
		keycodeMap[HUAN_KEY_N] = "HUAN_KEY_N";
		keycodeMap[HUAN_KEY_O] = "HUAN_KEY_O";
		keycodeMap[HUAN_KEY_P] = "HUAN_KEY_P";
		keycodeMap[HUAN_KEY_Q] = "HUAN_KEY_Q";
		keycodeMap[HUAN_KEY_R] = "HUAN_KEY_R";
		keycodeMap[HUAN_KEY_S] = "HUAN_KEY_S";
		keycodeMap[HUAN_KEY_T] = "HUAN_KEY_T";
		keycodeMap[HUAN_KEY_U] = "HUAN_KEY_U";
		keycodeMap[HUAN_KEY_V] = "HUAN_KEY_V";
		keycodeMap[HUAN_KEY_W] = "HUAN_KEY_W";
		keycodeMap[HUAN_KEY_X] = "HUAN_KEY_X";
		keycodeMap[HUAN_KEY_Y] = "HUAN_KEY_Y";
		keycodeMap[HUAN_KEY_Z] = "HUAN_KEY_Z";
		return keycodeMap;

	}
	Application* Application::instance = nullptr;

	Application::Application(): myLayerStack()
	{
		HUAN_CORE_ASSERT(!instance, "Application already exists!")
		instance = this;
		Huan::Log::init();
		createKeycodeMap();
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

				for (Layer* layer : myLayerStack)
					layer->onUpdate();

				myWindow->onUpdate();
			}
			HUAN_CORE_TRACE("Application closed!");
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
