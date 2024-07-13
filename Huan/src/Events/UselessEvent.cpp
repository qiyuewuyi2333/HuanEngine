#include "Events/UselessEvent.h"

namespace Huan
{
	UselessEvent::UselessEvent()
		:Event()
	{
		this->handled = true;
	}
	std::string UselessEvent::toString() const
	{
		return getName();
	}

}