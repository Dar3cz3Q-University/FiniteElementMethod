#pragma once

#include "Configuration.h"

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/bundled/ostream.h>
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#ifndef RUNNING_TEST

#define LOG_TRACE(...)  Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)   Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)   Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)  Log::GetLogger()->critical(__VA_ARGS__)

#else

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)

#endif

