#include "pch.h"

#include "Application.h"

// TODO: Debug print should be associated with LOG_LEVEL

int main(int argc, char** argv)
{
	Init();

	try
	{
		PROFILE_SCOPE("Application");

		Simulation simulation(FileTypeEnum::TEXT, "../Input/Grids/Styropian31x31.txt");
		simulation.Run();
	}
	catch (const std::exception& e)
	{
		LOG_CRITICAL(e.what());
	}

	ShutDown();

	std::cin.get();
}
