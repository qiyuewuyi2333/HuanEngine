#pragma once
#include "Events/Event.h"

namespace Huan
{
	class HUAN_API UselessEvent : public Event
	{
	public:
		UselessEvent();
		virtual ~UselessEvent() = default;


		EVENT_CLASS_CATEGORY(EventCategory::None)
		EVENT_CLASS_TYPE(None)


		std::string toString() const override;
	};
}
