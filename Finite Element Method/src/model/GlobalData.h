#pragma once

#include "Grid.h"

class GlobalData {
public:
	GlobalData() {}

private:
	int m_SimulationTime;
	int m_SimulationStepTime;
	double m_Conductivity;
	double m_Alpha;
	double m_Tot;
	double m_InitialTemp;
	double m_Density;
	double m_SpecificHeat;
	Grid m_Grid;
};
