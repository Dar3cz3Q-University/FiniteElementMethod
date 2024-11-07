#include "pch.h"

#include "TXTFileReader.h"

TXTFileReader::TXTFileReader() {}

const std::string& TXTFileReader::GetFileType() const
{
    return m_ReaderName;
}

GlobalData TXTFileReader::Read(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
        throw std::invalid_argument("File '" + path.string() + "' not found");

    std::ifstream file(path);
    
    if (!file.is_open())
        throw std::runtime_error("Cannot open: '" + path.string() + "'");

    DataTypeEnum dataType = DataTypeEnum::VARIABLES;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> words;

        while (iss >> word) words.push_back(word);

        if (words[0][0] == '*')
        {
            dataType = StringToDataTypeEnum(words[0]);
            continue;
        }
        
        if (dataType == DataTypeEnum::VARIABLES)
        {
            std::string tempWord = words.size() == 2 ? words[0] : words[0] + " " + words[1];
            GlobalDataEnum variable = StringToGlobalDataEnum(tempWord);

            m_GlobalDataVariableSetters.at(variable)(words.back());
        }
        else if (dataType == DataTypeEnum::NODES)
        {
            std::vector<std::string> values = Split(line, ',');

            Node tempNode(std::stod(values[1]), std::stod(values[2]));
            m_GlobalData.AddNodeToGrid(std::stoi(values[0]), tempNode);
        }
        else if (dataType == DataTypeEnum::ELEMENTS)
        {
			std::vector<std::string> values = Split(line, ',');

			Element tempElement;
            for (auto it = values.begin() + 1; it != values.end(); it++)
                tempElement.AddNode(std::stoi(*it), m_GlobalData.GetNode(std::stoi(*it)));

            m_GlobalData.AddElementToGrid(std::stoi(values[0]), tempElement);
        }
    }

    file.close();

    return m_GlobalData;
}
