cmake_minimum_required(VERSION 3.8)

project(ThirdParty CXX)



option(SPDLOG_BUILD_SHARED "Build shared library" ON)

# Include sub-projects.
add_subdirectory ("glfw")
add_subdirectory ("spdlog")
add_subdirectory ("glad")
add_subdirectory ("imgui")
add_subdirectory ("glm")

