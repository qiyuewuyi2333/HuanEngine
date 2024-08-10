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
    const std::unique_ptr<RendererAPI>& getCurrentRendererAPI() const;

  private:
    std::unique_ptr<RendererAPI> myRendererAPI;
};
} // namespace Huan