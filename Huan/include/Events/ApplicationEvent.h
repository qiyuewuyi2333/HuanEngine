#pragma once
#include "Event.h"

namespace Huan
{
	class HUAN_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height)
		{
		}

		unsigned int getWidth() const { return width; }
		unsigned int getHeight() const { return height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

	private:
		unsigned int width, height;
	};
	class HUAN_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};
	class HUAN_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};
	class HUAN_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};
	class HUAN_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};

}

