#include "interface/Huan.h"
#include "SandboxApp.h"
#include "ExampleLayer.h"


Huan::Application* Huan::createApplication()
{
	Application::instance = new SandboxApp();
	return Application::instance;
}

SandboxApp::SandboxApp()
{
	this->pushLayer(new ExampleLayer());
	this->pushOverlay(new Huan::ImGuiLayer());
}

SandboxApp::~SandboxApp()
{	
}


