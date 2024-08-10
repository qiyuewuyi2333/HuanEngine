#pragma once
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/RendererConfig.h"
#include "Renderer/Shader.h"
#include "imgui_internal.h"
#include "Huan/Core.h"
#include "Huan/Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"


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
    std::unique_ptr<Window> myWindow;
    LayerStack myLayerStack;
    bool isRunning = true;
    /**
     * @brief For first triangle test
     *
     */
    std::shared_ptr<CurrentVertexArray> vertexArray;
    std::shared_ptr<CurrentVertexBuffer> vertexBuffer;
    std::shared_ptr<CurrentIndexBuffer> indexBuffer;
    
    std::unique_ptr<Shader> shader;
};
inline Application* createApplication();

} // namespace Huan
