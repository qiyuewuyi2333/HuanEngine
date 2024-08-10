#include "Renderer/Scene.h"
#include "Renderer/VertexArray.h"

namespace Huan
{
Scene::Scene(std::shared_ptr<VertexArray> vertexArray)
 : myVertexArray(vertexArray)
{
}
VertexArray& Scene::getVertexArray() const
{
    return *myVertexArray;
}
} // namespace Huan