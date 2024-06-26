#include "Events/Event.h"

namespace Huan
{
	EventCategory operator|(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	EventCategory operator&(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

	std::string Event::toString() const
	{ return getName(); }

	bool Event::isInCategory(EventCategory category) const
	{
		return static_cast<int>(category) & getCategoryFlags();
	}

	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}
