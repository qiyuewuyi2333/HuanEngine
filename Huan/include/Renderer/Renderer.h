#pragma once
#include "HuanPCH.h"
#include "Renderer/RendererConfig.h"
#include "RenderCommand.h"
#include "Renderer/Shader.h"
#include "Renderer/Scene.h"
namespace Huan
{
enum RendererAPIName
{
    None,
    OpenGL,
    Vulkan
};
class HUAN_API Renderer
{
  public:
    static Renderer& getInstance()
    {
        static Renderer instance;
        return instance;
    }
    Renderer();
    void render(Ref<Shader>& shader, Scene& scene);
    const Scope<RenderCommand>& getMyRenderCommand() const;

  private:
    Scope<RenderCommand> myRenderCommand;
};
} // namespace Huan