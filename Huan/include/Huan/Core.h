#pragma once

#ifdef HUAN_PLATFORM_WINDOWS
	#ifdef HUAN_BUILD_DLL
		#define HUAN_API __declspec(dllexport)
	#else
		#define HUAN_API __declspec(dllimport)
	#endif
#else
	#error Huan only support Windows!
#endif