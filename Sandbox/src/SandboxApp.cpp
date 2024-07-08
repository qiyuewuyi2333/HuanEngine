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
}

SandboxApp::~SandboxApp()
{	
}

