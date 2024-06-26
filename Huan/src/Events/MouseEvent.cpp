#include "Events/MouseEvent.h"

namespace Huan
{
	MouseEvent::MouseEvent(const float x, const float y): mouseX(x), mouseY(y)
	{
	}

	float MouseEvent::getX() const
	{ return mouseX; }

	float MouseEvent::getY() const
	{ return mouseY; }

	std::string MouseEvent::toString() const
	{
		std::stringstream ss;
		ss << "MouseEvent: " << mouseX << ", " << mouseY;
		return ss.str();
	}

	MouseScrolledEvent::MouseScrolledEvent(const float _xOffset, const float _yOffset): xOffset(_xOffset), yOffset(_yOffset)
	{
	}

	float MouseScrolledEvent::getXOffset() const
	{ return xOffset; }

	float MouseScrolledEvent::getYOffset() const
	{ return yOffset; }

	std::string MouseScrolledEvent::toString() const
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
		return ss.str();
	}

	int MouseButtonEvent::getMouseButton() const
	{ return button; }

	MouseButtonEvent::MouseButtonEvent(const int _button): button(_button)
	{
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(const int _button): MouseButtonEvent(_button)
	{
	}

	std::string MouseButtonPressedEvent::toString() const
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << button;
		return ss.str();
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int _button): MouseButtonEvent(_button)
	{
	}

	std::string MouseButtonReleasedEvent::toString() const
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << button;
		return ss.str();
	}
}
