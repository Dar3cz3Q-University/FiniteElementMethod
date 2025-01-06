#pragma once

#include "Simulation.h"
#include "UniversalElement.h"

#include "Timer.h"
#include "Configuration.h"

#include "multithreading/ThreadPool.h"

void Init()
{
	std::cout.precision(10);

	Log::Init();
	ThreadPool::GetInstance()->Start(THREADS_COUNT);
	IntegrationPointDerivatives::GetInstance();
	UniversalElement::GetInstance();
}

void ShutDown()
{
	// Running destructors for singleton classes

	ThreadPool::GetInstance()->~ThreadPool();
	IntegrationPointDerivatives::GetInstance()->~IntegrationPointDerivatives();
	UniversalElement::GetInstance()->~UniversalElement();
}
