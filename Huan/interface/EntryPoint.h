#pragma once
#ifdef HUAN_PLATFORM_WINDOWS

extern Huan::Application* Huan::createApplication();

int main(int argc, char** argv)
{
    HUAN_PROFILE_BEGIN_SESSION("StartUp", "HuanProfile-StartUp.json");
    auto app = Huan::createApplication();
    ImGui::SetCurrentContext(Huan::Application::getImGuiContext());
    HUAN_PROFILE_END_SESSION();
    HUAN_PROFILE_BEGIN_SESSION("Runtime", "HuanProfile-Runtime.json");
    app->run();
    HUAN_PROFILE_END_SESSION();
    HUAN_PROFILE_BEGIN_SESSION("ShutDown", "HuanProfile-ShutDown.json");
    delete app;
    HUAN_PROFILE_END_SESSION();

    return 0;
}
#endif //
