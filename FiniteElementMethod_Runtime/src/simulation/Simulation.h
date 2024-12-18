#pragma once

#include "FileReaderFactory.h"
#include "GlobalData.h"
#include "GridGenerator.h"
#include "EquationSolver.h"

#include "gtest/gtest.h"

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
	Grid m_Grid;
	std::unique_ptr<FileReader> m_FileReader;

private:
	void DisplayData() const;

public:
	FRIEND_TEST(Global_H_MatrixTest, GeneratesValidMatrixFor_Test1_4_4);
	FRIEND_TEST(Global_H_MatrixTest, GeneratesValidMatrixFor_Test2_4_4);

	FRIEND_TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test1_4_4);
	FRIEND_TEST(Global_P_VectorTest, GeneratesValidVectorFor_Test2_4_4);
};

