#include "Simulation.h"

Simulation::Simulation(FileTypeEnum fileType, const std::filesystem::path& path)
{
	FileReaderFactory fileFactory;
	m_FileReader = fileFactory.CreateFileReader(fileType);

	try 
	{
		m_SimulationData = m_FileReader->Read(path);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return;
	}

	m_Initialized = true;
}

void Simulation::Run()
{
	if (!m_Initialized)
		throw std::logic_error("Object not initialized");

	std::cout << m_SimulationData << "\n";

	std::cout << "Running Gauss Integrals" << "\n";

	//NumericalMethods::Integrals
}
