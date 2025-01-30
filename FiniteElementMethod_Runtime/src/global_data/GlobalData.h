#pragma once

#include "GlobalDataEnum.h"

class GlobalData 
{
public:
	GlobalData();

public:
	inline void SetSimulationTime(int simulationTime) { m_SimulationTime = simulationTime; }
	inline void SetSimulationStepTime(int simulationStepTime) { m_SimulationStepTime = simulationStepTime; }
	inline void SetConductivity(double conductivity) { m_Conductivity.first = conductivity; }
	inline void SetAlpha(double alpha) { m_Alpha.first = alpha; }
	inline void SetTot(double tot) { m_Tot.first = tot; }
	inline void SetInitialTemp(double initialTemp) { m_InitialTemp = initialTemp; }
	inline void SetDensity(double density) { m_Density.first = density; }
	inline void SetSpecificHeat(double specificHeat) { m_SpecificHeat.first = specificHeat; }
	inline void SetReadElementsNumber(int readElementsNumber) { m_ReadElementsNumber = readElementsNumber; }
	inline void SetReadNodesNumber(int readNodesNumber) { m_ReadNodesNumber = readNodesNumber; }

	inline int GetSimulationTime() const { return m_SimulationTime; }
	inline int GetSimulationStepTime() const { return m_SimulationStepTime; }
	inline double GetConductivity() const { return m_Conductivity.first; }
	inline double GetAlpha() const { return m_Alpha.first; }
	inline double GetTot() const { return m_Tot.first; }
	inline double GetInitialTemp() const { return m_InitialTemp; }
	inline double GetDensity() const { return m_Density.first; }
	inline double GetSpecificHeat() const { return m_SpecificHeat.first; }
	inline int GetReadElementsNumber() const { return m_ReadElementsNumber; }
	inline int GetReadNodesNumber() const { return m_ReadNodesNumber; }

	// Second
	inline void SetConductivity_2(double conductivity) { m_Conductivity.second = conductivity; }
	inline void SetAlpha_2(double alpha) { m_Alpha.second = alpha; }
	inline void SetTot_2(double tot) { m_Tot.second = tot; }
	inline void SetDensity_2(double density) { m_Density.second = density; }
	inline void SetSpecificHeat_2(double specificHeat) { m_SpecificHeat.second = specificHeat; }

	inline double GetConductivity_2() const { return m_Conductivity.second; }
	inline double GetAlpha_2() const { return m_Alpha.second; }
	inline double GetTot_2() const { return m_Tot.second; }
	inline double GetDensity_2() const { return m_Density.second; }
	inline double GetSpecificHeat_2() const { return m_SpecificHeat.second; }

private:
	int m_SimulationTime = 0;
	int m_SimulationStepTime = 0;
	std::pair<double, double> m_Conductivity;
	std::pair<double, double> m_Alpha;
	std::pair<double, double> m_Tot;
	std::pair<double, double> m_Density;
	std::pair<double, double> m_SpecificHeat;
	double m_InitialTemp;
	int m_ReadElementsNumber = 0;
	int m_ReadNodesNumber = 0;

public:
	friend class TXTFileReader;
	friend std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);
};

std::ostream& operator<<(std::ostream& os, const GlobalData& globalData);
