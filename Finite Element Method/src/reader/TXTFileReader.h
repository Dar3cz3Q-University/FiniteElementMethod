#pragma once

#include "FileReader.h"

#include <iostream>

class TXTFileReader : public FileReader
{
public:
	const std::string& getFileType() const override;
	GlobalData read(const std::filesystem::path& path) const override;
};

