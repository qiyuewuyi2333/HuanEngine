#include "interface/Huan.h"

class SandboxApp : public Huan::Application
{
public:
	SandboxApp()
	{
	}

	~SandboxApp() override
	{
	}

	void run() override
	{
		HUAN_CLIENT_INFO("Hello, I'm Sandbox. ");
		Huan::WindowResizeEvent event(1920, 1080);
		HUAN_CLIENT_INFO(event.toString());
	}
};

Huan::Application* Huan::createApplication()
{
	return new SandboxApp();
}
