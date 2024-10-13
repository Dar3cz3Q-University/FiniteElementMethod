#include "pch.h"

#include "GlobalDataEnum.h"

GlobalDataEnum StringToGlobalDataEnum(const std::string& str)
{
	for (const auto& pair : GLOBAL_DATA_ENUM_DEFINITIONS)
		if (pair.second == str)
			return pair.first;

	throw std::invalid_argument("Unknown string value: " + str);
}

const std::string& EnumToString(GlobalDataEnum globalDataEnum)
{
	return GLOBAL_DATA_ENUM_DEFINITIONS.at(globalDataEnum);
}
