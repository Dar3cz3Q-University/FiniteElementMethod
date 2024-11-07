#include "pch.h"

#include "Simulation.h"

Simulation::Simulation()
{
	Node point1(0, 0), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);
	//Node point1(0.01, -0.01), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);

	m_SimulationData.AddNodeToGrid(1, point1);
	m_SimulationData.AddNodeToGrid(2, point2);
	m_SimulationData.AddNodeToGrid(3, point3);
	m_SimulationData.AddNodeToGrid(4, point4);

	Element element;
	element.AddNode(1, point1);
	element.AddNode(2, point2);
	element.AddNode(3, point3);
	element.AddNode(4, point4);

	element.Calculate();

	m_SimulationData.AddElementToGrid(1, element);

	m_Initialized = true;
}

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

	m_SimulationData.ValidateData();

	m_Initialized = true;
}

Simulation::Simulation(double x0, double x, double y0, double y, int nodes_x, int nodes_y)
{
	GridGenerator gridGenerator;

	try
	{
		m_SimulationData.SetGrid(gridGenerator.generate(x0, x, y0, y, nodes_x, nodes_y));
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

	std::cout << "Running Simulation" << "\n";

	std::cout << m_SimulationData << "\n";

	return;
}
