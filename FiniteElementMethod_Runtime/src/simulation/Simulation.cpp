#include "pch.h"

#include "Simulation.h"

Simulation::Simulation(FileTypeEnum fileType, const std::filesystem::path& path)
{
	LOG_TRACE("Creating file factory");

	FileReaderFactory fileFactory;
	m_FileReader = fileFactory.CreateFileReader(fileType);

	try 
	{
		DataSet dataset = m_FileReader->Read(path);
		m_SimulationData = dataset.globalData;
		m_Grid = dataset.grid;
	}
	catch (const std::invalid_argument& e)
	{
		LOG_CRITICAL(e.what());
		return;
	}

	m_Initialized = true;
}

Simulation::Simulation(double x0, double x, double y0, double y, int nodes_x, int nodes_y)
{
	GridGenerator gridGenerator;

	try
	{
		m_Grid = gridGenerator.generate(x0, x, y0, y, nodes_x, nodes_y);
	}
	catch (const std::invalid_argument& e)
	{
		LOG_CRITICAL(e.what());
		return;
	}

	m_Initialized = true;
}

void Simulation::Run()
{
	if (!m_Initialized)
		throw std::logic_error("Object not initialized");

	LOG_INFO("Displaying simulation data and grid");
	
	std::cout << m_SimulationData;
	std::cout << m_Grid;

	LOG_INFO("Running Simulation...");

	m_Grid.GenerateNecessaryData(m_SimulationData.GetConductivity());

	m_Grid.DisplayAllCalculatedData();

	return;
}
