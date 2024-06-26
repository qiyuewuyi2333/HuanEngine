#include "Events/KeyEvent.h"

namespace Huan
{
	KeyEvent::KeyEvent(const int _keyCode): keyCode(_keyCode)
	{}

	int KeyEvent::getKeyCode() const
	{ return keyCode; }

	KeyPressedEvent::KeyPressedEvent(const int _keyCode, const int _repeatCount): KeyEvent(_keyCode), repeatCount(_repeatCount)
	{}

	int KeyPressedEvent::getRepeatCount() const
	{ return repeatCount; }

	std::string KeyPressedEvent::toString() const
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
		return ss.str();
	}

	KeyReleasedEvent::KeyReleasedEvent(const int _keycode): KeyEvent(_keycode)
	{}

	std::string KeyReleasedEvent::toString() const
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << keyCode;
		return ss.str();
	}

	KeyTypedEvent::KeyTypedEvent(const int _keycode): KeyEvent(_keycode)
	{}

	std::string KeyTypedEvent::toString() const
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << keyCode;
		return ss.str();
	}
}
