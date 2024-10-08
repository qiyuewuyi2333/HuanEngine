#pragma	once
#include "HuanPCH.h"
#include "Events/Event.h"
#include "Events/EventDispatcher.h"
#include "util/TimeStep.h"
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
		virtual void onUpdate(TimeStep timeStep) {}
		virtual void onEvent(Event& event) {}
		virtual void onImGuiRender() {};
		const std::string& getName() const;

	protected:
		EventDispatcher dispatcher;
		std::string myDebugName;

	};
}
