#pragma once

#include "TXTFileReader.h"
#include "FileTypeEnum.h"

#include <unordered_map>
#include <functional>
#include <memory>

class FileReaderFactory
{
public:
	FileReaderFactory();

public:
	std::unique_ptr<FileReader> CreateFileReader(FileTypeEnum fileType);

private:
	std::unordered_map<FileTypeEnum, std::function<std::unique_ptr<FileReader>()>> m_FactoryMap;
};

