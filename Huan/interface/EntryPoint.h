#pragma once
#ifdef HUAN_PLATFORM_WINDOWS

extern Huan::Application* Huan::createApplication();

int main(int argc, char** argv)
{
	auto app = Huan::createApplication();
	Huan::ApplicationLocator::provide(app);

	app->run();
	delete app;
	return 0;
}
#endif // 
