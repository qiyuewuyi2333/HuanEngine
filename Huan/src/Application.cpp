#pragma once

#include "Huan/Application.h"

#include "Events/ApplicationEvent.h"
#include "util/Log.h"

namespace Huan
{
	Application::Application()
	{
		Huan::Log::init();
		HUAN_CORE_CRITICAL("Initialized Log! ");
		// WindowResizeEvent event(500,400);
		// HUAN_CORE_INFO(event.toString());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (true);
	}
	
}
