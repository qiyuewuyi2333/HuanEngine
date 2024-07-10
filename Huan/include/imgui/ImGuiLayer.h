#pragma once
#include "Events/MouseEvent.h"
#include "Huan/Core.h"
#include "Layer/Layer.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace Huan
{
	class HUAN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;

		void onEvent(Event& e) override;

		bool handleMouseMovedEvent(MouseMovedEvent& e);
		bool handleMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool handleMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool handleMouseScrolledEvent(MouseScrolledEvent& e);
		bool handleKeyPressedEvent(KeyPressedEvent& e);
		bool handleKeyReleasedEvent(KeyReleasedEvent& e);
		bool handleKeyTypedEvent(KeyTypedEvent& e);
		bool handleWindowResizeEvent(WindowResizeEvent& e);

	private:
		float myTime = 0.0f;
	};
}

