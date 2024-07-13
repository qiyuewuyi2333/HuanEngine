#include "util/Input.h"

namespace Huan
{

	bool Input::isKeyPressed(int keycode)
	{
		return instance->isKeyPressedImpl(keycode);
	}

	bool Input::isMouseButtonPressed(int button)
	{
		return instance->isMouseButtonPressedImpl(button);
	}

	std::pair<float, float> Input::getMousePosition()
	{
		return instance->getMousePositionImpl();
	}

	float Input::getMouseX()
	{
		return instance->getMouseXImpl();
	}

	float Input::getMouseY()
	{
		return instance->getMouseYImpl();
	}

}
