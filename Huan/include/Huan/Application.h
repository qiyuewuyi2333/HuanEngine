#pragma once
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/RendererConfig.h"
#include "Renderer/Scene.h"
#include "Renderer/Shader.h"
#include "imgui_internal.h"
#include "Huan/Core.h"
#include "Huan/Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"
#include "Renderer/Renderer.h"
#include "util/TimeStep.h"

namespace Huan
{
std::unordered_map<int, std::string> createKeycodeMap();
class HUAN_API Application
{
  public:
    Application();
    virtual ~Application();

    void run();
    void onEvent(Event& e);
    bool onWindowClose(WindowCloseEvent& e);

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);

    Window& getWindow();
    ImGuiLayer* imGuiLayer;
    static ImGuiContext* imGuiContext;

    static Application* getInstance();
    static ImGuiContext* getImGuiContext();
    static bool setImGuiContext(ImGuiContext* context);
    static Application* instance;

  private:
    Scope<Window> myWindow;
    LayerStack myLayerStack;
    bool isRunning = true;
    float myLastFrameTime = 0.0f;
};
inline Application* createApplication();

} // namespace Huan
