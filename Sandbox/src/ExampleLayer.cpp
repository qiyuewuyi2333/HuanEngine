#include "ExampleLayer.h"

#include "Events/KeyEvent.h"
#include "Huan/KeyCodes.h"
#include "Huan/MouseButtonCodes.h"
#include "imgui.h"
#include "util/Input.h"
#include "util/Log.h"
#include "Renderer/Utils/OrthogonalCamera.h"
#include "util/TimeStep.h"

ExampleLayer::ExampleLayer() : Layer("Example"), myRenderer(Huan::Renderer::getInstance())
{
    HUAN_CLIENT_INFO("Created Example Layer");
    shader = std::make_unique<Huan::Shader>("../../../../Resource/Shaders/test1/test1.vert",
                                            "../../../../Resource/Shaders/test1/test1.frag");

    float triangleVertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.8f,  1.0f};
    float quadVertices1[] = {-0.01f, 1.0f,  0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.01f, 1.0f,  0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
                             -0.01f, -1.0f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.01f, -1.0f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f};

    float quadVertices2[] = {1.0f,  -0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,  0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
                             -1.0f, -0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, -1.0f, 0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f};
    unsigned int indices[] = {0, 1, 2};
    unsigned int quadIndices[] = {0, 1, 3, 2, 3, 0};
    Huan::BufferLayout layout = {{Huan::ShaderDataType::Float3, "a_Position"},
                                 {Huan::ShaderDataType::Float4, "a_Color"}};

    myCamera = std::make_shared<Huan::OrthogonalCamera>(0.0f, 1.0f, 0.0f, 1.0f);

    // triangle
    std::shared_ptr<Huan::VertexArray> triangleArray = std::make_shared<CurrentVertexArray>();
    triangleArray->bind();
    std::shared_ptr<Huan::VertexBuffer> triangleVertexBuffer =
        std::make_shared<CurrentVertexBuffer>(triangleVertices, sizeof(triangleVertices));
    triangleVertexBuffer->bind();
    std::shared_ptr<Huan::IndexBuffer> triangleIndexBuffer1 =
        std::make_shared<CurrentIndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    triangleIndexBuffer1->bind();
    triangleVertexBuffer->setLayout(layout);
    triangleArray->addVertexBuffer(triangleVertexBuffer);
    triangleArray->setIndexBuffer(triangleIndexBuffer1);
    triangleArray->unbind();
    myScene1 = std::make_unique<Huan::Scene>(triangleArray, myCamera);

    // quad1
    std::shared_ptr<Huan::VertexArray> quadArray1 = std::make_shared<CurrentVertexArray>();
    quadArray1->bind();
    std::shared_ptr<Huan::VertexBuffer> quadVertexBuffer1 =
        std::make_shared<CurrentVertexBuffer>(quadVertices1, sizeof(quadVertices1));
    quadVertexBuffer1->bind();
    quadVertexBuffer1->setLayout(layout);
    quadArray1->addVertexBuffer(quadVertexBuffer1);
    std::shared_ptr<Huan::IndexBuffer> quadIndexBuffer =
        std::make_shared<CurrentIndexBuffer>(quadIndices, sizeof(quadIndices) / sizeof(unsigned int));
    quadIndexBuffer->bind();
    quadArray1->setIndexBuffer(quadIndexBuffer);
    quadArray1->unbind();
    myScene2 = std::make_unique<Huan::Scene>(quadArray1, myCamera);

    // quad2
    std::shared_ptr<Huan::VertexArray> quadArray2 = std::make_shared<CurrentVertexArray>();
    quadArray2->bind();
    std::shared_ptr<Huan::VertexBuffer> quadVertexBuffer2 =
        std::make_shared<CurrentVertexBuffer>(quadVertices2, sizeof(quadVertices2));
    quadVertexBuffer2->bind();
    quadVertexBuffer2->setLayout(layout);
    quadArray2->addVertexBuffer(quadVertexBuffer2);
    quadIndexBuffer->bind();
    quadArray2->setIndexBuffer(quadIndexBuffer);
    quadArray2->unbind();
    myScene3 = std::make_unique<Huan::Scene>(quadArray2, myCamera);
}

void ExampleLayer::onAttach()
{
}

void ExampleLayer::onDetach()
{
}

void ExampleLayer::onUpdate(Huan::TimeStep timeStep)
{
    if (Huan::Input::isKeyPressed(HUAN_KEY_LEFT))
        myCamera->move({timeStep, 0.0f, 0.0f});
    else if (Huan::Input::isKeyPressed(HUAN_KEY_RIGHT))
        myCamera->move({-timeStep, 0.0f, 0.0f});

    if (Huan::Input::isKeyPressed(HUAN_KEY_UP))
        myCamera->move({0.0f, timeStep, 0.0f});
    else if (Huan::Input::isKeyPressed(HUAN_KEY_DOWN))
        myCamera->move({0.0f, -timeStep, 0.0f});

    if (Huan::Input::isKeyPressed(HUAN_KEY_A))
        myCamera->rotate(timeStep);
    else if (Huan::Input::isKeyPressed(HUAN_KEY_D))
        myCamera->rotate(-timeStep);
    HUAN_CLIENT_INFO("x,y,z:{},{},{}",myCamera->getPosition().x, myCamera->getPosition().y, myCamera->getPosition().z);
    myRenderer.getMyRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    myRenderer.getMyRenderCommand()->clear();

    myRenderer.render(*shader, *myScene1);
    myRenderer.render(*shader, *myScene2);
    myRenderer.render(*shader, *myScene3);
}
void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::End();
}

void ExampleLayer::onEvent(Huan::Event& event)
{
    // HUAN_CLIENT_INFO("{0}", event.toString());
    if (event.getEventType() == Huan::EventType::KeyPressed)
    {
        Huan::KeyPressedEvent& e = (Huan::KeyPressedEvent&)event;
        if (e.getKeyCode() == HUAN_KEY_TAB)
        {
            HUAN_CLIENT_INFO("Tab key is pressed");
        }
    }
}
