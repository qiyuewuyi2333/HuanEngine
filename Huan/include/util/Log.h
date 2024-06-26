#pragma once
#include "HuanPCH.h"
#include "Huan/Core.h"

namespace Huan
{
	class HUAN_API Log
	{
	public:
		static void init();
		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return sCoreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return sClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};
}

#define HUAN_CORE_TRACE(...)		::Huan::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HUAN_CORE_INFO(...)			::Huan::Log::getCoreLogger()->info(__VA_ARGS__)
#define HUAN_CORE_WARN(...)			::Huan::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HUAN_CORE_ERROR(...)		::Huan::Log::getCoreLogger()->error(__VA_ARGS__)
#define HUAN_CORE_CRITICAL(...)		::Huan::Log::getCoreLogger()->critical(__VA_ARGS__)

#define HUAN_CLIENT_TRACE(...)		::Huan::Log::getClientLogger()->trace(__VA_ARGS__)
#define HUAN_CLIENT_INFO(...)		::Huan::Log::getClientLogger()->info(__VA_ARGS__)
#define HUAN_CLIENT_WARN(...)		::Huan::Log::getClientLogger()->warn(__VA_ARGS__)
#define HUAN_CLIENT_ERROR(...)		::Huan::Log::getClientLogger()->error(__VA_ARGS__)
#define HUAN_CLIENT_CRITICAL(...)	::Huan::Log::getClientLogger()->critical(__VA_ARGS__)



