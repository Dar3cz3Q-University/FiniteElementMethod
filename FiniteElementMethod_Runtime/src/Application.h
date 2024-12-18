#pragma once

#include "Configuration.h"
#include "Simulation.h"
#include "UniversalElement.h"

#include "multithreading/ThreadPool.h"

void Init()
{
	std::cout.precision(10);

	Log::Init();
	ThreadPool::GetInstance()->Start(THREADS_COUNT);
}

void ShutDown()
{
	// Running destructors for singleton classes

	ThreadPool::GetInstance()->~ThreadPool();
	IntegrationPointDerivatives::GetInstance()->~IntegrationPointDerivatives();
	UniversalElement::GetInstance()->~UniversalElement();
}
