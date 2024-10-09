#pragma once

#include "GlobalData.h"

#include <string>
#include <filesystem>

class FileReader
{
public:
	virtual const std::string& getFileType() const = 0;
	virtual GlobalData read(const std::filesystem::path& path) const = 0;
};

