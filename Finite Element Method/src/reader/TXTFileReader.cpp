#include "TXTFileReader.h"

const std::string& TXTFileReader::getFileType() const
{
    return ".txt File";
}

GlobalData TXTFileReader::read(const std::filesystem::path& path) const
{
    if (!std::filesystem::exists(path))
    {
        std::cerr << "File '" << path << "' not found. Cannot import data" << "\n";
        return GlobalData();
    }

    return GlobalData();
}
