#include "interface/Huan.h"
#include "SandboxApp.h"
#include "ExampleLayer.h"


Huan::Application* Huan::createApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
{
	this->pushLayer(new ExampleLayer());
	this->pushOverlay(new Huan::ImGuiLayer());
}

SandboxApp::~SandboxApp()
{	
}


