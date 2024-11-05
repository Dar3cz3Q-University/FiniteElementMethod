#include "pch.h"

#include "DataTypeEnum.h"

DataTypeEnum StringToDataTypeEnum(const std::string& str)
{
	for (const auto& pair : DATA_TYPE_ENUM_DEFINITIONS)
		if (pair.second == str)
			return pair.first;

	return DataTypeEnum::VARIABLES;
}

const std::string& EnumToString(DataTypeEnum dataTypeEnum)
{
	return DATA_TYPE_ENUM_DEFINITIONS.at(dataTypeEnum);
}
