#include "Renderer/Scene.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/VertexArray.h"
#include <memory>

namespace Huan
{

Scene::Scene(Ref<VertexArray> vertexArray, Ref<Camera> camera, Ref<Texture> texture) : myCamera(camera),myTexture(texture)
{
    if (vertexArray)
        myVertexArrays.push_back(vertexArray);
    uColor = nullptr;
}
std::vector<Ref<VertexArray>>& Scene::getVertexArrays()
{
    return myVertexArrays;
}
Ref<Camera> Scene::getCamera() const
{
    return myCamera;
}
Ref<Texture> Scene::getTexture() const
{
    return myTexture;
}

} // namespace Huan