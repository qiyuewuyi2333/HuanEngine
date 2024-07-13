#include "ExampleLayer.h"
#include "Events/KeyEvent.h"
#include "util/Input.h"
#include "Huan/KeyCodes.h"
#include "Huan/MouseButtonCodes.h"
#include "util/Log.h"

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

}

void ExampleLayer::onEvent(Huan::Event& event)
{
	HUAN_CLIENT_INFO("{0}", event.toString());
	if(event.getEventType() == Huan::EventType::KeyPressed)
	{
		Huan::KeyPressedEvent& e = (Huan::KeyPressedEvent&)event;
		if(e.getKeyCode() == HUAN_KEY_TAB)
		{
			HUAN_CLIENT_INFO("Tab key is pressed");
		}
	}
}
