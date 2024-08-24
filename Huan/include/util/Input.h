#pragma once
#include "Huan/Core.h"

namespace Huan
{

	class HUAN_API Input
	{
	public:
		static bool isKeyPressed(int keycode);
		static bool isMouseButtonPressed(int button);
		static std::pair<float, float> getMousePosition();
		static float getMouseX();
		static float getMouseY();
        static void setCursorMode(uint32_t mode);
	public:
		virtual bool isKeyPressedImpl(int keycode) const = 0;
		virtual bool isMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float> getMousePositionImpl() const = 0;
		virtual float getMouseXImpl() const = 0;
		virtual float getMouseYImpl() const = 0;
        virtual void setCursorModeImpl(uint32_t mode) = 0;
        protected:
        static Input* instance;
	};
}
