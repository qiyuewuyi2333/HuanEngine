#pragma once
#include "Huan/Core.h"
#include "Huan/Window.h"
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

		Window& getWindow();
		static Application* getInstance();
		static Application* instance;

	private:
		std::unique_ptr<Window> myWindow;
		LayerStack myLayerStack;
		bool isRunning = true;
	};
	inline Application* createApplication();

}
