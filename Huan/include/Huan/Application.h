#pragma once
#include "Core.h"
#include "Window.h"

namespace Huan
{
	class HUAN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
		std::unique_ptr<Window> myWindow;
		bool isRunning = true;
	};

	Application* createApplication();
}
