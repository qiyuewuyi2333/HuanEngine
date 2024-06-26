#include "interface/Huan.h"
#include "SandboxApp.h"


Huan::Application* Huan::createApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
{
	HUAN_CLIENT_CRITICAL("Initialized Log! ");
}

SandboxApp::~SandboxApp()
{	
}

void SandboxApp::run()
{
	HUAN_CLIENT_INFO("Hello, I'm Sandbox. ");
	Huan::WindowResizeEvent event(1920, 1080);
	HUAN_CLIENT_INFO(event.toString());
	HUAN_CLIENT_INFO(event.getName());
}
