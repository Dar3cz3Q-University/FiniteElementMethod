#include "pch.h"

#include "Simulation.h"

int main(int argc, char** argv)
{
	std::cout.precision(10);

	try
	{
		Simulation simulation;
		//Simulation simulation(FileTypeEnum::TEXT, "../Input/Grids/Test1_4_4.txt");
		//Simulation simulation(0.0, 0.1, 0.0, 0.1, 4, 6);
		simulation.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}

	std::cin.get();
}
