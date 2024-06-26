#include "Events/EventDispatcher.h"

namespace Huan
{
	EventDispatcher::EventDispatcher(Event& event) : event(event)
	{
	}

	template <typename T>
	bool EventDispatcher::dispatch(EventFunc<T> func)
	{
		if (event.get().getEventType() == T::getStaticType())
		{
			event.get().handled = func(event.get());
			return true;
		}
		return false;
	}
}
