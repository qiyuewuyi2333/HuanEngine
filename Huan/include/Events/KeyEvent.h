#pragma once
#include "Event.h"

namespace Huan
{
	class HUAN_API KeyEvent : public Event
	{
	public:
		KeyEvent(const int _keyCode) : keyCode(_keyCode) {}
		inline int getKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)
	protected:
		int keyCode;
	};
	class HUAN_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const int _keyCode, const int _repeatCount) : KeyEvent(_keyCode), repeatCount(_repeatCount) {}
		inline int getRepeatCount() const { return repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};
	class HUAN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int _keycode)
			: KeyEvent(_keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
	class HUAN_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int _keycode)
			: KeyEvent(_keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}