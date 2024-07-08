#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
	:Layer("Example")
{

}

void ExampleLayer::onAttach()
{
}

void ExampleLayer::onDetach()
{
}

void ExampleLayer::onUpdate()
{
	HUAN_CLIENT_INFO("ExampleLayer::onUpdate");
}

void ExampleLayer::onEvent(Huan::Event& event)
{
	HUAN_CLIENT_INFO("{0}", event.toString());
}
