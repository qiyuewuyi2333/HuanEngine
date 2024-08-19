#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <fstream>
#include <memory>
#include <optional>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <array>
#include <filesystem>
#include <thread>

#include "DebugTools/Instrumentor.h"

#include "spdlog/spdlog.h"

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// ImGui
#include "imgui.h"

#ifdef HUAN_PLATFORM_WINDOWS
#include <Windows.h>
    
#endif

#ifdef HUAN_USING_OPENGL
    #include "glad/glad.h"
    #include "GLFW/glfw3.h"
#endif