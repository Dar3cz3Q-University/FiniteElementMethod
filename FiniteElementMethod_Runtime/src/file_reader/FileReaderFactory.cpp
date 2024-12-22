#include "pch.h"

#include "FileReaderFactory.h"

FileReaderFactory::FileReaderFactory()
{
    LOG_TRACE("Creating file factory");

	m_FactoryMap[FileTypeEnum::TEXT] = []() { return std::make_unique<TXTFileReader>(); };
}

std::unique_ptr<FileReader> FileReaderFactory::CreateFileReader(FileTypeEnum fileType)
{
    LOG_TRACE("Creating file reader");

    auto it = m_FactoryMap.find(fileType);

    if (it != m_FactoryMap.end())
        return it->second();

    throw std::invalid_argument("Unsupported file type");
}
