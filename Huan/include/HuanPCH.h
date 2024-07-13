#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <memory>
#include "spdlog/spdlog.h"


#ifdef HUAN_PLATFORM_WINDOWS
	#include <Windows.h>
	#ifdef HUAN_OPENGL
		#include "glad/glad.h"
		#include "GLFW/glfw3.h"
	#endif
#endif