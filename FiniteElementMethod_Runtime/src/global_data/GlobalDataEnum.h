#pragma once

enum GlobalDataEnum
{
	SIMULATION_TIME = 0,
	SIMULATION_STEP_TIME,
	CONDUCTIVITY,
	CONDUCTIVITY_2,
	ALPHA,
	ALPHA_2,
	TOT,
	TOT_2,
	INITIAL_TEMP,
	DENSITY,
	DENSITY_2,
	SPECIFIC_HEAT,
	SPECIFIC_HEAT_2,
	NODES_NUMBER,
	ELEMENTS_NUMBER
};

inline std::unordered_map<GlobalDataEnum, std::string> GLOBAL_DATA_ENUM_DEFINITIONS = {
	{GlobalDataEnum::SIMULATION_TIME, "SimulationTime"},
	{GlobalDataEnum::SIMULATION_STEP_TIME, "SimulationStepTime"},
	{GlobalDataEnum::CONDUCTIVITY, "Conductivity"},
	{GlobalDataEnum::CONDUCTIVITY_2, "Conductivity_2"},
	{GlobalDataEnum::ALPHA, "Alfa"},
	{GlobalDataEnum::ALPHA_2, "Alfa_2"},
	{GlobalDataEnum::TOT, "Tot"},
	{GlobalDataEnum::TOT_2, "Tot_2"},
	{GlobalDataEnum::INITIAL_TEMP, "InitialTemp"},
	{GlobalDataEnum::DENSITY, "Density"},
	{GlobalDataEnum::DENSITY_2, "Density_2"},
	{GlobalDataEnum::SPECIFIC_HEAT, "SpecificHeat"},
	{GlobalDataEnum::SPECIFIC_HEAT_2, "SpecificHeat_2"},
	{GlobalDataEnum::NODES_NUMBER, "Nodes number"},
	{GlobalDataEnum::ELEMENTS_NUMBER, "Elements number"},
};

GlobalDataEnum StringToGlobalDataEnum(const std::string& str);
const std::string& EnumToString(GlobalDataEnum globalDataEnum);
