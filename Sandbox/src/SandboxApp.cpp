#include "interface/Huan.h"
#include "SandboxApp.h"


Huan::Application* Huan::createApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
{
}

SandboxApp::~SandboxApp()
{	
}

