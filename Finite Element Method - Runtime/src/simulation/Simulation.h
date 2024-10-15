#pragma once

#include "FileReaderFactory.h"
#include "GlobalData.h"
#include "GridGenerator.h"

class Simulation
{
public:
	Simulation(FileTypeEnum fileType, const std::filesystem::path& path);
	Simulation(double x0, double x, double y0, double y, int nodes_x, int nodes_y);

public:
	void Run();

private:
	bool m_Initialized = false;
	GlobalData m_SimulationData;
	std::unique_ptr<FileReader> m_FileReader;
};

