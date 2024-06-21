#pragma once
#ifdef HUAN_PLATFORM_WINDOWS

extern Huan::Application* Huan::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Huan::CreateApplication();
	app->run();
	delete app;
	return 0;
}
#endif // 
