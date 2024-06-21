
#include "interface/Huan.h"
class SandboxApp : public Huan::Application
{
public:
	SandboxApp()
	{
	}

	~SandboxApp()
	{
	}

	void run() override
	{
		std::cout << "Hello, I'm Huan1\n";
	}
};
Huan::Application* Huan::CreateApplication()
{
	return new SandboxApp();
}

