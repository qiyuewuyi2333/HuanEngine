#pragma once
#include "Event.h"

namespace Huan
{
	class HUAN_API MouseEvent : public Event
	{
	public:
		MouseEvent(const float x, const float y)
			: mouseX(x), mouseY(y)
		{
		}

		float getX() const { return mouseX; }
		float getY() const { return mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseEvent: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	private:
		float mouseX;
		float mouseY;
	};

	class HUAN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float _xOffset, const float _yOffset) : xOffset(_xOffset), yOffset(_yOffset)
		{
		}

		float getXOffset() const { return xOffset; }
		float getYOffset() const { return yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	private:
		float xOffset, yOffset;
	};

	class HUAN_API MouseButtonEvent : public Event
	{
	public:
		int getMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

	protected:
		MouseButtonEvent(const int _button) : button(_button)
		{
		}

		int button;
	};

	class HUAN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int _button) : MouseButtonEvent(_button)
		{
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HUAN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int _button) : MouseButtonEvent(_button)
		{
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
