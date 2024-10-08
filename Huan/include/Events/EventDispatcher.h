#pragma once
#include "Events/UselessEvent.h"
#include "Huan/Core.h"

namespace Huan
{
/**
 *  @brief similar to a kind of dynamic dispatch. this function dispatches the event to the function that matches the
 *type of the event.
 *	@author Huan
 *
 */
class EventDispatcher
{
  private:
    template <typename T>
    using EventFunc = std::function<bool(T&)>;

  public:
    EventDispatcher() = delete;
    EventDispatcher(EventDispatcher&) = delete;

    EventDispatcher(Event& event);
    void reset(Event& e);
    template <typename T>
    bool dispatch(EventFunc<T> func)
    {
        if (event.get().getEventType() == T::getStaticType())
        {
            T* specificEvent = dynamic_cast<T*>(&event.get());
            if (specificEvent)
            {
                event.get().handled = func(*specificEvent);
                return true;
            }
        }
        return false;
    }

  private:
    std::reference_wrapper<Event> event;

  public:
    static UselessEvent uselessEvent;
};

} // namespace Huan
