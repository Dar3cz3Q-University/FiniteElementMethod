#pragma once

enum DataTypeEnum
{
	VARIABLES = 0,
	NODES,
	ELEMENTS,
	BC,
	MATERIAL1,
	MATERIAL2
};

inline std::unordered_map<DataTypeEnum, std::string> DATA_TYPE_ENUM_DEFINITIONS = {
	{ DataTypeEnum::VARIABLES, "*Variables" },
	{ DataTypeEnum::NODES, "*Node" },
	{ DataTypeEnum::ELEMENTS, "*Element," },
	{ DataTypeEnum::BC, "*BC" },
	{ DataTypeEnum::MATERIAL1, "*Material1" },
	{ DataTypeEnum::MATERIAL2, "*Material2" }
};

DataTypeEnum StringToDataTypeEnum(const std::string& str);
const std::string& EnumToString(DataTypeEnum dataTypeEnum);
