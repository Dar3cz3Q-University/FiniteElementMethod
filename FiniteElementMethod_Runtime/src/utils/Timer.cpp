#include "pch.h"
#include "Timer.h"

Timer::Timer(const char* name)
	: m_Name(name), m_Stopped(false)
{
	m_StartTimePoint = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
	if (!m_Stopped)
		Stop();
}

void Timer::Stop()
{
	auto endTimePoint = std::chrono::steady_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	auto duration = end - start;

	LOG_INFO("{} took: {} microseconds", m_Name, duration);

	m_Stopped = true;
}
