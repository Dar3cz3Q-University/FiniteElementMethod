#include "pch.h"

#include "Application.h"

// TODO: Debug print should be associated with LOG_LEVEL

int main(int argc, char** argv)
{
	Init();

	try
	{
		PROFILE_SCOPE("Application");

		Simulation simulation(FileTypeEnum::TEXT, "../Input/Grids/Test3_31_31_kwadrat.txt");
		simulation.Run();
	}
	catch (const std::exception& e)
	{
		LOG_CRITICAL(e.what());
	}

	ShutDown();

	std::cin.get();
}
