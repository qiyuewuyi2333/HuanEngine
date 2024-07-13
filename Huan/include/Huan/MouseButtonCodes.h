#pragma once

namespace Huan
{
	namespace MouseButtonCodes
	{
		// from glfw3.h
		#ifdef HUAN_OPENGL	

			#define HUAN_MOUSE_BUTTON_1         0
			#define HUAN_MOUSE_BUTTON_2         1
			#define HUAN_MOUSE_BUTTON_3         2
			#define HUAN_MOUSE_BUTTON_4         3
			#define HUAN_MOUSE_BUTTON_5         4
			#define HUAN_MOUSE_BUTTON_6         5
			#define HUAN_MOUSE_BUTTON_7         6
			#define HUAN_MOUSE_BUTTON_8         7
			#define HUAN_MOUSE_BUTTON_LAST      HUAN_MOUSE_BUTTON_8
			#define HUAN_MOUSE_BUTTON_LEFT      HUAN_MOUSE_BUTTON_1
			#define HUAN_MOUSE_BUTTON_RIGHT     HUAN_MOUSE_BUTTON_2
			#define HUAN_MOUSE_BUTTON_MIDDLE    HUAN_MOUSE_BUTTON_3

		#endif // HUAN_OPENGL
	}
}