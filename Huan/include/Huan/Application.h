#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"

namespace Huan
{
	class HUAN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);
		bool onWindowClose(WindowCloseEvent& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> myWindow;
		LayerStack myLayerStack;
		bool isRunning = true;
	};

	Application* createApplication();
}
