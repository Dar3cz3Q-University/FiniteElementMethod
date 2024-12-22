#include "pch.h"

#include "Simulation.h"
#include "Timer.h"

Simulation::Simulation(FileTypeEnum fileType, const std::filesystem::path& path)
{
	LOG_INFO("Initializing simulation with file");

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

	LOG_INFO("Grid initialized");

	m_Initialized = true;
}

Simulation::Simulation(double x0, double x, double y0, double y, int nodes_x, int nodes_y)
{
	LOG_TRACE("Generating grid");

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

	LOG_INFO("Grid initialized");

	m_Initialized = true;
}

void Simulation::Run()
{
	if (!m_Initialized)
		throw std::logic_error("Grid is not initialized. Cannot run simulation");

	DisplayData();
	
	LOG_INFO("Calculating necessary data");

	{
		PROFILE_SCOPE("Necessary data calculations");
		m_Grid.Calculate(m_SimulationData);
	}

	LOG_INFO("Running simulation...");

	EquationSolver solver(
		m_SimulationData,
		m_Grid.GetH(),
		m_Grid.GetC(),
		m_Grid.GetP()
	);

	{
		PROFILE_SCOPE("Simulation");
		solver.Run();
	}

	LOG_INFO("Simulation ended");

	return;
}

void Simulation::DisplayData() const
{
	std::cout << "\nGlobal Data:\n";
	std::cout << m_SimulationData;

	std::cout << "\nGrid:\n";
	std::cout << m_Grid << "\n";
}
