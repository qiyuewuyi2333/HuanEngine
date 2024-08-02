#pragma once
#include "Event.h"

namespace Huan
{
class HUAN_API WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(unsigned int width, unsigned int height);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    std::string toString() const override;

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

  private:
    unsigned int width, height;
};
class HUAN_API WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent();

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};
class HUAN_API AppTickEvent : public Event
{
  public:
    AppTickEvent();

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};
class HUAN_API AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent();

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};
class HUAN_API AppRenderEvent : public Event
{
  public:
    AppRenderEvent();

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

} // namespace Huan
