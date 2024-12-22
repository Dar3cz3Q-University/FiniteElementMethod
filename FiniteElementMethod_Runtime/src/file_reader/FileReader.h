#pragma once

#include "GlobalData.h"
#include "Grid.h"

struct DataSet
{
	GlobalData globalData;
	Grid grid;
};

class FileReader
{
public:
	virtual ~FileReader() = default;
	virtual const std::string& GetFileType() const = 0;
	virtual DataSet Read(const std::filesystem::path& path) = 0;
};

