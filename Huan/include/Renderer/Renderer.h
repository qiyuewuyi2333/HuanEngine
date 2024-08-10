#pragma once
namespace Huan
{
enum RendererAPI
{
    None,
    OpenGL,
    Vulkan
};
class Renderer
{
public:
    virtual void init() = 0;
    virtual void render() = 0;
    static RendererAPI getAPI() { return sAPI; }
protected:
    static RendererAPI sAPI;
};

} // namespace Huan