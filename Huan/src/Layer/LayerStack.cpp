#include "Layer/LayerStack.h"

namespace Huan
{
	LayerStack::LayerStack()
	{
		myLayerInsert = myLayers.begin();
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : myLayers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		myLayerInsert = myLayers.emplace(myLayerInsert, layer);
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
			--myLayerInsert;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(myLayers.begin(), myLayers.end(), overlay);
		if (it != myLayers.end()) myLayers.erase(it);
	}
}

