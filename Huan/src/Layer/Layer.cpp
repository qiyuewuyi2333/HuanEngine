#include "Layer/Layer.h"

namespace Huan
{
	Layer::Layer(const std::string& name)
		: myDebugName(name)
	{
	}
	Layer::~Layer()
	{
	}
	const std::string& Layer::getName() const
	{
		return myDebugName;
	}
}
