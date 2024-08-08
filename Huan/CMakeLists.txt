cmake_minimum_required (VERSION 3.8)


project("Huan")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

add_library (${PROJECT_NAME} SHARED ${SRC_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/HuanPCH.h)

# WINDOWS
target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_PLATFORM_WINDOWS)
# DYNAMIC
target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_BUILD_DLL)
# DEBUG
target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_DEBUG)
# OPENGL
target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_OPENGL)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/imgui")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/spdlog/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/glfw/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/glad/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/third_party/glm")


target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)


