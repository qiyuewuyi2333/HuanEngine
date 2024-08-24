#include "interface/Huan.h"
#include "SandboxApp.h"
#include "ExampleLayer.h"
#include "Sandbox.h"

Huan::Application* Huan::createApplication()
{
	Application::instance = new SandboxApp();
	return Application::instance;
}

SandboxApp::SandboxApp()
{
	this->pushLayer(new Sandbox());
}

SandboxApp::~SandboxApp()
{	
}


