#pragma once
#include "Event.h"

namespace Huan
{
	class HUAN_API KeyEvent : public Event
	{
	public:
		KeyEvent(const int _keyCode);
		inline int getKeyCode() const;

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

	protected:
		int keyCode;
	};
	class HUAN_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const int _keyCode, const int _repeatCount);
		inline int getRepeatCount() const;

		std::string toString() const override;

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int repeatCount;
	};
	class HUAN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int _keycode);

		std::string toString() const override;

		EVENT_CLASS_TYPE(KeyReleased)
	};
	class HUAN_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const int _keycode);

		std::string toString() const override;

		EVENT_CLASS_TYPE(KeyTyped)
	};
}