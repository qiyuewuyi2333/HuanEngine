#pragma once

#include "Layer.h"
#include "Huan/Core.h"

namespace Huan
{
	class HUAN_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return myLayers.begin(); }
		std::vector<Layer*>::iterator end() { return myLayers.end(); }

	private:
		std::vector<Layer*> myLayers;
		std::vector<Layer*>::iterator myLayerInsert;
	};
}
