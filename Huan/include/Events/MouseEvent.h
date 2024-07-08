#pragma once
#include "Event.h"

namespace Huan
{
	class HUAN_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const float x, const float y);

		float getX() const;
		float getY() const;

		std::string toString() const override;

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	private:
		float mouseX;
		float mouseY;
	};

	class HUAN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float _xOffset, const float _yOffset);

		float getXOffset() const;
		float getYOffset() const;

		std::string toString() const override;

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	private:
		float xOffset, yOffset;
	};

	class HUAN_API MouseButtonEvent : public Event
	{
	public:
		int getMouseButton() const;

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	protected:
		MouseButtonEvent(const int _button);

		int button;
	};

	class HUAN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int _button);

		std::string toString() const override;

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HUAN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int _button);

		std::string toString() const override;

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
