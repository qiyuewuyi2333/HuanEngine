#pragma once

#include "Renderer/Utils/Camera.h"
#include "VertexArray.h"
#include <memory>
#include <vector>
namespace Huan
{
/**
 * @brief Easy scene for renderer testing
 *
 */
class Scene
{
  public:
    Scene() = delete;
    Scene(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Camera> camera);
    virtual ~Scene() = default;
    std::vector<std::shared_ptr<VertexArray>>& getVertexArrays();
    std::shared_ptr<Camera> getCamera() const;

  private:
    std::vector<std::shared_ptr<VertexArray>> myVertexArrays;
    std::shared_ptr<Camera> myCamera;
};

} // namespace Huan