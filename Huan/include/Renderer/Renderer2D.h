#pragma once
#include "Renderer/RenderCommand.h"
#include "Scene.h"
#include "Shader.h"
#include "Huan/Core.h"
#include "Primitives/Color.h"
#include "Texture/Texture2D.h"

namespace Huan
{

struct Renderer2DData
{
    Ref<Camera>         camera;
    Ref<VertexArray>    quadVertexArray;
    Ref<VertexArray>    quadTextureVertexArray;
    Ref<Shader>         quadTextureShader;
    Ref<Texture>        myTexture;
    Ref<Texture>        myWhiteTexture;
};


class HUAN_API Renderer2D
{
public:
    static Renderer2D& getInstance()
    {
        static Renderer2D instance;
        return instance;
    }

    Renderer2D();
    Renderer2D(const Renderer2D&) = delete;

    void init();
    void shutdown();

    void loadScene(Ref<Scene> scene);
    void beginScene();
    void renderScene();
    void endScene();
    void setScene(Ref<Scene> scene);
    // primitives
    void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color);
    void drawQuad(const glm::vec3& position, const glm::vec2& size, const Color& color);
    void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture);
    void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture);

    // get
    const Scope<RenderCommand>& getRenderCommand() const;
  private:
    Scope<RenderCommand> myRenderCommand;
    // You might have many renderer to render one same scene
    Ref<Scene> myScene;
    Renderer2DData* myData;
};
} // namespace Huan