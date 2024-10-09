#pragma once

#include <string>

enum GlobalDataEnum
{
	SIMULATION_TIME = 0,
	SIMULATION_TIME_STEP,
	CONDUCTIVITY,
	ALPHA,
	TOT,
	INITIAL_TEMP,
	DENSITY,
	SPECIFIC_HEAT,
	NODES_NUMBER,
	ELEMENTS_NUMBER
};

inline const std::string GLOBAL_DATA_ENUM_DEFINITIONS[10] = {
	"SimulationTime",
	"SimulationStepTime",
	"Conductivity",
	"Alfa",
	"Tot",
	"InitialTemp",
	"Density",
	"SpecificHeat",
	"Nodes number",
	"Elements number"
};

inline const std::string& EnumToString(GlobalDataEnum globalDataEnum)
{
	return GLOBAL_DATA_ENUM_DEFINITIONS[globalDataEnum];
}
