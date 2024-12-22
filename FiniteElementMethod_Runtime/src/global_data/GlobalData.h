#pragma once

#include "Grid.h"
#include "GlobalDataEnum.h"

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
	inline void SetReadElementsNumber(int readElementsNumber) { m_ReadElementsNumber = readElementsNumber; }
	inline void SetReadNodesNumber(int readNodesNumber) { m_ReadNodesNumber = readNodesNumber; }

	inline int GetSimulationTime() const { return m_SimulationTime; }
	inline int GetSimulationStepTime() const { return m_SimulationStepTime; }
	inline double GetConductivity() const { return m_Conductivity; }
	inline double GetAlpha() const { return m_Alpha; }
	inline double GetTot() const { return m_Tot; }
	inline double GetInitialTemp() const { return m_InitialTemp; }
	inline double GetDensity() const { return m_Density; }
	inline double GetSpecificHeat() const { return m_SpecificHeat; }

private:
	int m_SimulationTime = 0;
	int m_SimulationStepTime = 0;
	double m_Conductivity = 0.0;
	double m_Alpha = 0.0;
	double m_Tot = 0.0;
	double m_InitialTemp = 0.0;
	double m_Density = 0.0;
	double m_SpecificHeat = 0.0;
	int m_ReadElementsNumber = 0;
	int m_ReadNodesNumber = 0;

public:
	friend class TXTFileReader;
	friend std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);
};

std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);
