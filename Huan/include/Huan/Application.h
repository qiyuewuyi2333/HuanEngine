#pragma once
#include "Core.h"
namespace Huan
{
	class HUAN_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void run();
	};

	Application* CreateApplication();
}
