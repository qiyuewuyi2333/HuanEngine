#pragma once
#include "HuanPCH.h"
#include "Renderer/RendererConfig.h"
#include "RenderCommand.h"
#include "Renderer/Shader.h"
#include "Renderer/Scene.h"
#include <memory>
namespace Huan
{
enum RendererAPIName
{
    None,
    OpenGL,
    Vulkan
};
class Renderer
{
  public:
    static Renderer& getInstance()
    {
        static Renderer instance;
        return instance;
    }
    Renderer();
    void render(Shader& shader, Scene& scene);
    const std::unique_ptr<RenderCommand>& getMyRenderCommand() const;

  private:
    std::unique_ptr<RenderCommand> myRenderCommand;
};
} // namespace Huan