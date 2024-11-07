#include "pch.h"

#include "GlobalData.h"

GlobalData::GlobalData() {}

std::ostream& operator<<(std::ostream& os, const GlobalData& globalData)
{
	os << EnumToString(GlobalDataEnum::SIMULATION_TIME) << " " << globalData.m_SimulationTime << "\n";
	os << EnumToString(GlobalDataEnum::SIMULATION_STEP_TIME) << " " << globalData.m_SimulationStepTime << "\n";
	os << EnumToString(GlobalDataEnum::CONDUCTIVITY) << " " << globalData.m_Conductivity << "\n";
	os << EnumToString(GlobalDataEnum::ALPHA) << " " << globalData.m_Alpha << "\n";
	os << EnumToString(GlobalDataEnum::TOT) << " " << globalData.m_Tot << "\n";
	os << EnumToString(GlobalDataEnum::INITIAL_TEMP) << " " << globalData.m_InitialTemp << "\n";
	os << EnumToString(GlobalDataEnum::DENSITY) << " " << globalData.m_Density << "\n";
	os << EnumToString(GlobalDataEnum::SPECIFIC_HEAT) << " " << globalData.m_SpecificHeat << "\n";

	return os;
}
