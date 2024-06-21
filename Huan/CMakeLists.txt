cmake_minimum_required (VERSION 3.8)


project("Huan")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

add_library (${PROJECT_NAME} SHARED ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_PLATFORM_WINDOWS)
target_compile_definitions(${PROJECT_NAME} PRIVATE HUAN_BUILD_DLL)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

