#include "Simulation.h"

int main(int argc, int** argv)
{
	try
	{
		Simulation simulation(FileTypeEnum::TEXT, "../Input/Grids/Test1_4_4.txt");
		simulation.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}
