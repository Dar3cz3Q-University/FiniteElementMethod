#include "pch.h"

#include "Application.h"

// TODO: All displaying should be dependent on LOG_LEVEL
// It is not implemented yet, so logs can be confusing if set on other than 'trace'

int main(int argc, char** argv)
{
	Init();

	try
	{
		PROFILE_SCOPE("Application");

		Simulation simulation(FileTypeEnum::TEXT, "../Input/Grids/Test2_4_4_MixGrid.txt");
		simulation.Run();
	}
	catch (const std::exception& e)
	{
		LOG_CRITICAL(e.what());
	}

	ShutDown();

	std::cin.get();
}
