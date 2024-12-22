#pragma once

#include <iostream>
#include <chrono>

#define _PROFILING_

#ifdef _PROFILING_
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name)
#define PROFILE_CORE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_CORE_FUNCTION()
#endif

class Timer
{
public:
	Timer(const char* name);
	~Timer();

private:
	const char* m_Name;
	std::chrono::steady_clock::time_point m_StartTimePoint;
	bool m_Stopped;

	void Stop();
};
