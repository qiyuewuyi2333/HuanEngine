#include "Layer/LayerStack.h"

namespace Huan
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : myLayers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		myLayers.emplace(myLayers.begin() + posToInsert, layer);
		++posToInsert;
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		myLayers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(myLayers.begin(), myLayers.end(), layer);
		if (it != myLayers.end())
		{
			myLayers.erase(it);
			--posToInsert;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(myLayers.begin(), myLayers.end(), overlay);
		if (it != myLayers.end()) myLayers.erase(it);
	}
}

