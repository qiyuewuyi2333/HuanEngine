#pragma once
#include "Events/Event.h"

namespace Huan
{
	/**
	 *  @brief similar to a kind of dynamic dispatch. this function dispatches the event to the function that matches the type of the event.
	 *	@author Huan
	 *
	 */
	class EventDispatcher
	{
	private:
		template <typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher() = delete;
		EventDispatcher(EventDispatcher&) = delete;

		EventDispatcher(Event& event);

		template <typename T>
		bool dispatch(EventFunc<T> func);

	private:
		std::reference_wrapper<Event> event;
	};
}
