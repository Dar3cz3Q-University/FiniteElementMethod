#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

enum DataTypeEnum
{
	VARIABLES = 0,
	NODES,
	ELEMENTS,
	BC
};

inline std::unordered_map<DataTypeEnum, std::string> DATA_TYPE_ENUM_DEFINITIONS = {
	{ DataTypeEnum::VARIABLES, "*Variables" },
	{ DataTypeEnum::NODES, "*Node" },
	{ DataTypeEnum::ELEMENTS, "*Element," },
	{ DataTypeEnum::BC, "*BC" }
};

DataTypeEnum StringToDataTypeEnum(const std::string& str);
const std::string& EnumToString(DataTypeEnum dataTypeEnum);
