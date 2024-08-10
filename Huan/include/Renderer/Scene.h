#pragma once

#include "VertexArray.h"
#include <memory>
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
    Scene(std::shared_ptr<VertexArray> vertexArray);
    virtual ~Scene() = default;
    VertexArray& getVertexArray() const;

  private:
    std::shared_ptr<VertexArray> myVertexArray;
};

} // namespace Huan