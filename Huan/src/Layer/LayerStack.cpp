#include "Layer/LayerStack.h"

namespace Huan
{
LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
    HUAN_PROFILE_FUNCTION();
    for (Layer* layer : myLayers)
        delete layer;
}

void LayerStack::pushLayer(Layer* layer)
{
    HUAN_PROFILE_FUNCTION();
    myLayers.emplace(myLayers.begin() + posToInsert, layer);
    ++posToInsert;
}

void LayerStack::pushOverlay(Layer* overlay)
{
    HUAN_PROFILE_FUNCTION();
    myLayers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer)
{
    HUAN_PROFILE_FUNCTION();
    auto it = std::find(myLayers.begin(), myLayers.end(), layer);
    if (it != myLayers.end())
    {
        myLayers.erase(it);
        --posToInsert;
    }
}

void LayerStack::popOverlay(Layer* overlay)
{
    HUAN_PROFILE_FUNCTION();
    auto it = std::find(myLayers.begin(), myLayers.end(), overlay);
    if (it != myLayers.end())
        myLayers.erase(it);
}
} // namespace Huan
