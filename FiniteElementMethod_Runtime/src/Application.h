#pragma once

#include "Simulation.h"
#include "multithreading/ThreadPool.h"

void Init()
{
	std::cout.precision(10);
	Log::Init();
	ThreadPool::GetInstance()->Start();
}
