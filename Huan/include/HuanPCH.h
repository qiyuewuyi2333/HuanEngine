#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <fstream>
#include <memory>
#include "spdlog/spdlog.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef HUAN_PLATFORM_WINDOWS
#include <Windows.h>
#ifdef HUAN_OPENGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#endif
#endif