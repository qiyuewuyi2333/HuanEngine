#pragma once
#include "Layer/LayerStack.h"
#include "util/Log.h"

class ExampleLayer : public Huan::Layer
{
public:
	ExampleLayer();
	~ExampleLayer() = default;

	void onAttach() override;
	void onDetach() override;
	void onUpdate() override;
	void onEvent(Huan::Event& event) override;
};