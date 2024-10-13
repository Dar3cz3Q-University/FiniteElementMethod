#pragma once

#include "Grid.h"

class GlobalData 
{
public:
	GlobalData();

public:
	inline void SetSimulationTime(int simulationTime) { m_SimulationTime = simulationTime; }
	inline void SetSimulationStepTime(int simulationStepTime) { m_SimulationStepTime = simulationStepTime; }
	inline void SetConductivity(double conductivity) { m_Conductivity = conductivity; }
	inline void SetAlpha(double alpha) { m_Alpha = alpha; }
	inline void SetTot(double tot) { m_Tot = tot; }
	inline void SetInitialTemp(double initialTemp) { m_InitialTemp = initialTemp; }
	inline void SetDensity(double density) { m_Density = density; }
	inline void SetSpecificHeat(double specificHeat) { m_SpecificHeat = specificHeat; }

	inline void AddElementToGrid(Element element) { m_Grid.AddElement(element); }
	inline void AddNodeToGrid(Node node) { m_Grid.AddNode(node); }

	inline void ReserveGridElements(int numberOfElements) { m_Grid.ReserveElements(numberOfElements); }
	inline void ReserveGridNodes(int numberOfNodes) { m_Grid.ReserveNodes(numberOfNodes); }

private:
	int m_SimulationTime = 0;
	int m_SimulationStepTime = 0;
	double m_Conductivity = 0.0;
	double m_Alpha = 0.0;
	double m_Tot = 0.0;
	double m_InitialTemp = 0.0;
	double m_Density = 0.0;
	double m_SpecificHeat = 0.0;
	Grid m_Grid;

public:
	friend std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);
};

std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);