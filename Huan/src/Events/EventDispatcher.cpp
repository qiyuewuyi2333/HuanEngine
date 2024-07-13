#include "Events/EventDispatcher.h"



namespace Huan
{
	UselessEvent EventDispatcher::uselessEvent = {};

	EventDispatcher::EventDispatcher(Event& event) : event(event)
	{
	}

	void EventDispatcher::reset(Event& e)
	{
		this->event = e;
	}
}
