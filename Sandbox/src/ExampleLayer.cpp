#include "ExampleLayer.h"

#include "Events/KeyEvent.h"
#include "Huan/Core.h"
#include "Huan/KeyCodes.h"
#include "Huan/MouseButtonCodes.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Buffer/BufferLayout.h"
#include "Renderer/Utils/OrthogonalCameraController.h"
#include "imgui.h"
#include "util/Input.h"
#include "util/Log.h"
#include "Renderer/Utils/OrthogonalCamera.h"
#include "util/TimeStep.h"
#include "Renderer/RendererConfig.h"
#include <memory>

ExampleLayer::ExampleLayer() : Layer("Example"), myRenderer(Huan::Renderer::getInstance())
{
    HUAN_CLIENT_INFO("Created Example Layer");
    shader = std::make_shared<Huan::CurrentShader>("../../../../Assets/Shaders/test1/test1.vert",
                                            "../../../../Assets/Shaders/test1/test1.frag");
    shader2 = std::make_shared<Huan::CurrentShader>("../../../../Assets/Shaders/test2/test2.vert",
                                            "../../../../Assets/Shaders/test2/test2.frag");
    Huan::Ref<Huan::Texture> texture = std::make_shared<Huan::CurrentTexture2D>("../../../../Assets/Textures/logo.png");
    float triangleVertices[] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.8f,  1.0f};
    float quadVertices1[] = {-0.01f, 1.0f,  0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.01f, 1.0f,  0.0f, 0.0f, 0.8f, 0.0f, 1.0f,
                             -0.01f, -1.0f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.01f, -1.0f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f};

    float quadVertices2[] = {1.0f,  -0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,  0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
                             -1.0f, -0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, -1.0f, 0.01f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f};
    float quadVertices3[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {0, 1, 2};
    unsigned int quadIndices[] = {0, 1, 3, 2, 3, 0};
    unsigned int quadIndices2[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Huan::BufferLayout layout = {{Huan::ShaderDataType::Float3, "inPosition"},
                                 {Huan::ShaderDataType::Float4, "inColor"}};
    Huan::BufferLayout layout2 = {{Huan::ShaderDataType::Float3, "inPosition"},
                                  {Huan::ShaderDataType::Float3, "inColor"},
                                  {Huan::ShaderDataType::Float2, "inTexCoord"}};
    myCameraController = std::make_shared<Huan::OrthogonalCameraController>(1280.0f / 720.0f);

    // triangle
    Huan::Ref<Huan::VertexArray> triangleArray = std::make_shared<Huan::CurrentVertexArray>();
    triangleArray->bind();
    Huan::Ref<Huan::VertexBuffer> triangleVertexBuffer =
        std::make_shared<Huan::CurrentVertexBuffer>(triangleVertices, sizeof(triangleVertices));
    triangleVertexBuffer->bind();
    Huan::Ref<Huan::IndexBuffer> triangleIndexBuffer1 =
        std::make_shared<Huan::CurrentIndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    triangleIndexBuffer1->bind();
    triangleVertexBuffer->setLayout(layout);
    triangleArray->addVertexBuffer(triangleVertexBuffer);
    triangleArray->setIndexBuffer(triangleIndexBuffer1);
    triangleArray->unbind();
    myScene1 = std::make_unique<Huan::Scene>(triangleArray, myCameraController->getCamera());

    // quad1
    Huan::Ref<Huan::VertexArray> quadArray1 = std::make_shared<Huan::CurrentVertexArray>();
    quadArray1->bind();
    Huan::Ref<Huan::VertexBuffer> quadVertexBuffer1 =
        std::make_shared<Huan::CurrentVertexBuffer>(quadVertices1, sizeof(quadVertices1));
    quadVertexBuffer1->bind();
    quadVertexBuffer1->setLayout(layout);
    quadArray1->addVertexBuffer(quadVertexBuffer1);
    Huan::Ref<Huan::IndexBuffer> quadIndexBuffer =
        std::make_shared<Huan::CurrentIndexBuffer>(quadIndices, sizeof(quadIndices) / sizeof(unsigned int));
    quadIndexBuffer->bind();
    quadArray1->setIndexBuffer(quadIndexBuffer);
    quadArray1->unbind();
    myScene2 = std::make_unique<Huan::Scene>(quadArray1, myCameraController->getCamera());

    // quad2
    Huan::Ref<Huan::VertexArray> quadArray2 = std::make_shared<Huan::CurrentVertexArray>();
    quadArray2->bind();
    Huan::Ref<Huan::VertexBuffer> quadVertexBuffer2 =
        std::make_shared<Huan::CurrentVertexBuffer>(quadVertices2, sizeof(quadVertices2));
    quadVertexBuffer2->bind();
    quadVertexBuffer2->setLayout(layout);
    quadArray2->addVertexBuffer(quadVertexBuffer2);
    quadIndexBuffer->bind();
    quadArray2->setIndexBuffer(quadIndexBuffer);
    quadArray2->unbind();
    myScene3 = std::make_unique<Huan::Scene>(quadArray2, myCameraController->getCamera());

    // quad3
    Huan::Ref<Huan::VertexArray> quadArray3 = std::make_shared<Huan::CurrentVertexArray>();
    quadArray3->bind();
    Huan::Ref<Huan::VertexBuffer> quadVertexBuffer3 =
        std::make_shared<Huan::CurrentVertexBuffer>(quadVertices3, sizeof(quadVertices3));
    quadVertexBuffer3->bind();
    quadVertexBuffer3->setLayout(layout2);
    quadArray3->addVertexBuffer(quadVertexBuffer3);
    Huan::Ref<Huan::IndexBuffer> quadIndexBuffer2 = 
        std::make_shared<Huan::CurrentIndexBuffer>(quadIndices2,sizeof(quadIndices2)/sizeof(unsigned int));
    quadIndexBuffer2->bind();
    quadArray3->setIndexBuffer(quadIndexBuffer2);
    quadArray3->unbind();
    myScene4 = std::make_unique<Huan::Scene>(quadArray3, myCameraController->getCamera(), texture);
}

void ExampleLayer::onAttach()
{
}

void ExampleLayer::onDetach()
{
}

void ExampleLayer::onUpdate(Huan::TimeStep timeStep)
{
    
    myCameraController->onUpdate(timeStep);
    
    myRenderer.getMyRenderCommand()->setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    myRenderer.getMyRenderCommand()->clear();

    myRenderer.render(shader,  *myScene1);
    myRenderer.render(shader2, *myScene4);
    
    myRenderer.render(shader,  *myScene3);
    myRenderer.render(shader,  *myScene2);
}
void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::End();
}

void ExampleLayer::onEvent(Huan::Event& event)
{
    myCameraController->onEvent(event);
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
