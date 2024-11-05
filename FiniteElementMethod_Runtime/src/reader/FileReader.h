#pragma once

#include "GlobalData.h"

class FileReader
{
public:
	virtual const std::string& GetFileType() const = 0;
	virtual GlobalData Read(const std::filesystem::path& path) = 0;
};

