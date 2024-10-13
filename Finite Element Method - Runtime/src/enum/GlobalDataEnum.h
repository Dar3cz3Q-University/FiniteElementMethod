#pragma once

enum GlobalDataEnum
{
	SIMULATION_TIME = 0,
	SIMULATION_STEP_TIME,
	CONDUCTIVITY,
	ALPHA,
	TOT,
	INITIAL_TEMP,
	DENSITY,
	SPECIFIC_HEAT,
	NODES_NUMBER,
	ELEMENTS_NUMBER
};

inline std::unordered_map<GlobalDataEnum, std::string> GLOBAL_DATA_ENUM_DEFINITIONS = {
	{GlobalDataEnum::SIMULATION_TIME, "SimulationTime"},
	{GlobalDataEnum::SIMULATION_STEP_TIME, "SimulationStepTime"},
	{GlobalDataEnum::CONDUCTIVITY, "Conductivity"},
	{GlobalDataEnum::ALPHA, "Alfa"},
	{GlobalDataEnum::TOT, "Tot"},
	{GlobalDataEnum::INITIAL_TEMP, "InitialTemp"},
	{GlobalDataEnum::DENSITY, "Density"},
	{GlobalDataEnum::SPECIFIC_HEAT, "SpecificHeat"},
	{GlobalDataEnum::NODES_NUMBER, "Nodes number"},
	{GlobalDataEnum::ELEMENTS_NUMBER, "Elements number"},
};

GlobalDataEnum StringToGlobalDataEnum(const std::string& str);
const std::string& EnumToString(GlobalDataEnum globalDataEnum);
