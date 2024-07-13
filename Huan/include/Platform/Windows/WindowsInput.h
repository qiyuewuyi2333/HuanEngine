#pragma once
#include "util/Input.h"
#include "platform/Windows/WindowsWindow.h"

namespace Huan
{
	class HUAN_API WindowsInput : public Input
	{
	public:
		WindowsInput();
		virtual bool isKeyPressedImpl(int keycode) const override;
		virtual bool isMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> getMousePositionImpl() const override;
		virtual float getMouseXImpl() const override;
		virtual float getMouseYImpl() const override;

	};
}