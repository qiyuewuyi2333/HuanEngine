#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Renderer/VertexArray.h"
#include "glad/glad.h"
#include <cstdint>

namespace Huan
{
void OpenGLRendererAPI::init()
{
    HUAN_PROFILE_FUNCTION();
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
{
    HUAN_PROFILE_FUNCTION();
    glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRendererAPI::clear()
{
    HUAN_PROFILE_FUNCTION();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRendererAPI::draw(const VertexArray& vertexArray)
{
    HUAN_PROFILE_FUNCTION();
    glDrawArrays(GL_TRIANGLES, 0, vertexArray.getVertexBufferCount());
    glBindTexture(GL_TEXTURE_2D, 0);
}
void OpenGLRendererAPI::drawIndexed(const VertexArray& vertexArray)
{
    HUAN_PROFILE_FUNCTION();
    glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRendererAPI::enableBlend()
{
    HUAN_PROFILE_FUNCTION();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void OpenGLRendererAPI::enableDepthTest()
{
    HUAN_PROFILE_FUNCTION();
    glEnable(GL_DEPTH_TEST);
}
void OpenGLRendererAPI::setCursorMode(uint32_t mode)
{
    HUAN_PROFILE_FUNCTION();
    switch (mode)
    {
    case 0:
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
    case 1:
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    default:
        HUAN_CORE_ASSERT(false, "Invalid cursor mode");
        break;
    }
}
} // namespace Huan