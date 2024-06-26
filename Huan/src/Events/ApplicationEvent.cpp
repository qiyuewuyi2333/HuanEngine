#include "Events/ApplicationEvent.h"

namespace Huan
{
	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height): width(width), height(height)
	{
	}

	unsigned int WindowResizeEvent::getWidth() const
	{ return width; }

	unsigned int WindowResizeEvent::getHeight() const
	{ return height; }

	std::string WindowResizeEvent::toString() const
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << width << ", " << height;
		return ss.str();
	}

	WindowCloseEvent::WindowCloseEvent() = default;
	AppTickEvent::AppTickEvent() = default;
	AppUpdateEvent::AppUpdateEvent() = default;
	AppRenderEvent::AppRenderEvent() = default;
}
