#include "util/Log.h"

#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace Huan
{
	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		sCoreLogger = spdlog::stdout_color_mt("Huan");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("App");
		sClientLogger->set_level(spdlog::level::trace);
	}
}


