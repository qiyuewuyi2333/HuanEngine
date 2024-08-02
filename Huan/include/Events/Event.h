#pragma once
#include "Huan/Core.h"
#include "HuanPCH.h"

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

EventCategory operator|(EventCategory lhs, EventCategory rhs);

EventCategory operator&(EventCategory lhs, EventCategory rhs);
// clang-format off
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
	virtual EventType getEventType() const override { return getStaticType(); }\
	virtual const char* getName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return static_cast<int>((category)); }
// clang-format on
class HUAN_API Event
{
  public:
    Event() = default;

  public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const;

    bool isInCategory(EventCategory category) const;

  public:
    bool handled = false;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.toString();
}
} // namespace Huan
