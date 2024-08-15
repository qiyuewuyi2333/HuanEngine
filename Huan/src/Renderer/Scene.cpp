#include "Renderer/Scene.h"
#include "Renderer/VertexArray.h"
#include <memory>

namespace Huan
{

Scene::Scene(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Camera> camera) : myCamera(camera)
{
    myVertexArrays.push_back(vertexArray);
}
std::vector<std::shared_ptr<VertexArray>>& Scene::getVertexArrays()
{
    return myVertexArrays;
}
std::shared_ptr<Camera> Scene::getCamera() const
{
    return myCamera;
}

} // namespace Huan