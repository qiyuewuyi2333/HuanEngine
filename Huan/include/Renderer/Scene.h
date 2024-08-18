#pragma once

#include "Renderer/Utils/Camera.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture/Texture.h"
namespace Huan
{
/**
 * @brief Easy scene for renderer testing
 *
 */
class HUAN_API Scene
{
  public:
    Scene() = delete;
    Scene(Ref<VertexArray> vertexArray, Ref<Camera> camera, Ref<Texture> texture = nullptr);
    virtual ~Scene() = default;
    std::vector<Ref<VertexArray>>& getVertexArrays();
    Ref<Camera> getCamera() const;
    Ref<Texture> getTexture() const;

  private:
    std::vector<Ref<VertexArray>> myVertexArrays;
    Ref<Camera> myCamera;
    Ref<Texture> myTexture;
public:
    Ref<glm::vec4> uColor;
};

} // namespace Huan