#pragma once

#include "FileReaderFactory.h"
#include "GlobalData.h"
#include "Integrals/Gauss.h"

class Simulation
{
public:
	Simulation(FileTypeEnum fileType, const std::filesystem::path& path);

public:
	void Run();

private:
	bool m_Initialized = false;
	GlobalData m_SimulationData;
	std::unique_ptr<FileReader> m_FileReader;
};

