#pragma once
#include <memory>

#ifdef HUAN_PLATFORM_WINDOWS
	#ifdef HUAN_BUILD_DLL
		#define HUAN_API __declspec(dllexport)
	#else
		#define HUAN_API __declspec(dllimport)
	#endif
#else
	#error Huan only support Windows!
#endif

#ifdef HUAN_DEBUG
	#define HUAN_ENABLE_ASSERTS
#endif


#ifdef HUAN_ENABLE_ASSERTS
	#define HUAN_CLIENT_ASSERT(x, ...) { if(!(x)) { HUAN_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HUAN_CORE_ASSERT(x, ...) { if(!(x)) { HUAN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HUAN_CLIENT_ASSERT(x, ...)
	#define HUAN_CORE_ASSERT(x, ...)
#endif

#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace Huan 
{

	template<typename T>
	using Scope = ::std::unique_ptr<T>;

	template<typename T>
	using Ref = ::std::shared_ptr<T>;

}