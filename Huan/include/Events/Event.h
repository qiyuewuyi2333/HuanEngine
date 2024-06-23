#pragma once

#include <functional>

#include "Huan/Core.h"
#include <string>
#include <sstream>

#define BIT(X) (1 << X)

namespace Huan
{
	enum class EventType : int
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
	};

	enum class EventCategory : int
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	inline EventCategory operator|(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	inline EventCategory operator&(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
	virtual EventType getEventType() const override { return getStaticType(); }\
	virtual const char* getName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return static_cast<int>((category)); }

	class HUAN_API Event
	{
		friend class EventDispatcher;

	public:
		Event() = default;

	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		bool isInCategory(EventCategory category) const
		{
			return static_cast<int>(category) & getCategoryFlags();
		}

	protected:
		bool handled = false;
	};

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

		EventDispatcher(Event& event)
			: event(event)
		{
		}

		template <typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (event.get().getEventType() == T::getStaticType())
			{
				event.get().handled = func(event.get());
				return true;
			}
			return false;
		}

	private:
		std::reference_wrapper<Event> event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}
