#include "Huan/Application.h"
#include "Events/EventDispatcher.h"
#include "Huan/Core.h"
#include "Huan/KeyCodes.h"
#include "HuanPCH.h"
#include "Renderer/Buffer/BufferLayout.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "util/Log.h"
#include "Renderer/RendererConfig.h"

namespace Huan
{
std::unordered_map<int, std::string> createKeycodeMap()
{
    std::unordered_map<int, std::string> keycodeMap;

    keycodeMap[HUAN_KEY_SPACE] = "HUAN_KEY_SPACE";
    keycodeMap[HUAN_KEY_APOSTROPHE] = "HUAN_KEY_APOSTROPHE";
    keycodeMap[HUAN_KEY_COMMA] = "HUAN_KEY_COMMA";
    keycodeMap[HUAN_KEY_MINUS] = "HUAN_KEY_MINUS";
    keycodeMap[HUAN_KEY_PERIOD] = "HUAN_KEY_PERIOD";
    keycodeMap[HUAN_KEY_SLASH] = "HUAN_KEY_SLASH";
    keycodeMap[HUAN_KEY_0] = "HUAN_KEY_0";
    keycodeMap[HUAN_KEY_1] = "HUAN_KEY_1";
    keycodeMap[HUAN_KEY_2] = "HUAN_KEY_2";
    keycodeMap[HUAN_KEY_3] = "HUAN_KEY_3";
    keycodeMap[HUAN_KEY_4] = "HUAN_KEY_4";
    keycodeMap[HUAN_KEY_5] = "HUAN_KEY_5";
    keycodeMap[HUAN_KEY_6] = "HUAN_KEY_6";
    keycodeMap[HUAN_KEY_7] = "HUAN_KEY_7";
    keycodeMap[HUAN_KEY_8] = "HUAN_KEY_8";
    keycodeMap[HUAN_KEY_9] = "HUAN_KEY_9";
    keycodeMap[HUAN_KEY_SEMICOLON] = "HUAN_KEY_SEMICOLON";
    keycodeMap[HUAN_KEY_EQUAL] = "HUAN_KEY_EQUAL";
    keycodeMap[HUAN_KEY_A] = "HUAN_KEY_A";
    keycodeMap[HUAN_KEY_B] = "HUAN_KEY_B";
    keycodeMap[HUAN_KEY_C] = "HUAN_KEY_C";
    keycodeMap[HUAN_KEY_D] = "HUAN_KEY_D";
    keycodeMap[HUAN_KEY_E] = "HUAN_KEY_E";
    keycodeMap[HUAN_KEY_F] = "HUAN_KEY_F";
    keycodeMap[HUAN_KEY_G] = "HUAN_KEY_G";
    keycodeMap[HUAN_KEY_H] = "HUAN_KEY_H";
    keycodeMap[HUAN_KEY_I] = "HUAN_KEY_I";
    keycodeMap[HUAN_KEY_J] = "HUAN_KEY_J";
    keycodeMap[HUAN_KEY_K] = "HUAN_KEY_K";
    keycodeMap[HUAN_KEY_L] = "HUAN_KEY_L";
    keycodeMap[HUAN_KEY_M] = "HUAN_KEY_M";
    keycodeMap[HUAN_KEY_N] = "HUAN_KEY_N";
    keycodeMap[HUAN_KEY_O] = "HUAN_KEY_O";
    keycodeMap[HUAN_KEY_P] = "HUAN_KEY_P";
    keycodeMap[HUAN_KEY_Q] = "HUAN_KEY_Q";
    keycodeMap[HUAN_KEY_R] = "HUAN_KEY_R";
    keycodeMap[HUAN_KEY_S] = "HUAN_KEY_S";
    keycodeMap[HUAN_KEY_T] = "HUAN_KEY_T";
    keycodeMap[HUAN_KEY_U] = "HUAN_KEY_U";
    keycodeMap[HUAN_KEY_V] = "HUAN_KEY_V";
    keycodeMap[HUAN_KEY_W] = "HUAN_KEY_W";
    keycodeMap[HUAN_KEY_X] = "HUAN_KEY_X";
    keycodeMap[HUAN_KEY_Y] = "HUAN_KEY_Y";
    keycodeMap[HUAN_KEY_Z] = "HUAN_KEY_Z";
    return keycodeMap;
}
Application* Application::instance = nullptr;
ImGuiContext* Application::imGuiContext = nullptr;

Application::Application() : myLayerStack()
{
    HUAN_CORE_ASSERT(!instance, "Application already exists!")
    instance = this;
    Log::init();
    HUAN_CORE_INFO("Initialized Log! ");
    // create window
    myWindow = std::unique_ptr<Window>(Window::create());
    // use Application's onEvent as the window's callback func
    myWindow->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));

    imGuiLayer = new ImGuiLayer();
    pushOverlay(imGuiLayer);

    shader = std::make_unique<Shader>("../../../../Resource/Shaders/test1/test1.vert",
                                      "../../../../Resource/Shaders/test1/test1.frag");

    float triangleVertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.8f,  1.0f};
    unsigned int indices[] = {0, 1, 2};

    vertexArray = std::make_shared<CurrentVertexArray>();
    vertexArray->bind();
    vertexBuffer = std::make_shared<CurrentVertexBuffer>(triangleVertices, sizeof(triangleVertices));
    vertexBuffer->bind();
    indexBuffer = std::make_shared<CurrentIndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    indexBuffer->bind();
    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->setLayout(layout);

    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);

    vertexArray->unbind();
}

Application::~Application()
{
}

void Application::run()
{
    const WindowResizeEvent e(1280, 720);

    if (e.isInCategory(EventCategory::EventCategoryApplication))
    {
        HUAN_CLIENT_TRACE(e.toString());

        while (isRunning)
        {
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            vertexArray->bind();
            shader->use();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            vertexArray->unbind();

            for (Layer* layer : myLayerStack)
                layer->onUpdate();

            imGuiLayer->begin();
            for (Layer* layer : myLayerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            myWindow->onUpdate();
        }
        HUAN_CORE_TRACE("Application closed!");
    }
}

void Application::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

    for (auto it = myLayerStack.end(); it != myLayerStack.begin();)
    {
        --it;
        (*it)->onEvent(e);
        if (e.handled)
            break;
    }
}

bool Application::onWindowClose(WindowCloseEvent& e)
{
    isRunning = false;
    return true;
}

void Application::pushLayer(Layer* layer)
{
    myLayerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* layer)
{
    myLayerStack.pushOverlay(layer);
    layer->onAttach();
}

Window& Application::getWindow()
{
    return *myWindow;
}

Application* Application::getInstance()
{
    return instance;
}

ImGuiContext* Application::getImGuiContext()
{
    return imGuiContext;
}
bool Application::setImGuiContext(ImGuiContext* context)
{
    Application::imGuiContext = context;
    return true;
}
} // namespace Huan
