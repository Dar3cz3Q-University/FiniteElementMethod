#pragma once

#include "TXTFileReader.h"
#include "FileTypeEnum.h"

class FileReaderFactory
{
public:
	FileReaderFactory();

public:
	std::unique_ptr<FileReader> CreateFileReader(FileTypeEnum fileType);

private:
	std::unordered_map<FileTypeEnum, std::function<std::unique_ptr<FileReader>()>> m_FactoryMap;
};

