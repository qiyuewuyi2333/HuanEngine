#pragma	once
#include "HuanPCH.h"
#include "Events/Event.h"
#include "Huan/Core.h"

namespace Huan
{
	class HUAN_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const;

	protected:
		std::string myDebugName;
	};
}
