#include "pch.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
	spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%n]: %v%$");
	s_Logger = spdlog::stdout_color_mt("FEM");
	s_Logger->set_level(spdlog::level::trace);

	LOG_TRACE("Logger initialized");
}
