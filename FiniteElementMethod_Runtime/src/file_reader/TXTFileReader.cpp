#include "pch.h"

#include "TXTFileReader.h"

TXTFileReader::TXTFileReader() {}

const std::string& TXTFileReader::GetFileType() const
{
    return m_ReaderName;
}

DataSet TXTFileReader::Read(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
        throw std::ios_base::failure("File '" + path.string() + "' not found");

    std::ifstream file(path);
    
    if (!file.is_open())
        throw std::runtime_error("Cannot open: '" + path.string() + "'");

    LOG_TRACE("Reading data from '{}'", path.string());

    DataTypeEnum dataType = DataTypeEnum::VARIABLES;
    std::string line;

    LOG_TRACE("Reading '{}' section", EnumToString(dataType));

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> words;

        while (iss >> word) words.push_back(word);

        if (words[0][0] == '*')
        {
            dataType = StringToDataTypeEnum(words[0]);
            LOG_TRACE("Reading '{}' section", words[0]);
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
            m_Grid.AddNode(std::stoi(values[0]), tempNode);
        }
        else if (dataType == DataTypeEnum::ELEMENTS)
        {
			std::vector<std::string> values = Split(line, ',');

			Element tempElement;
            for (auto it = values.begin() + 1; it != values.end(); it++)
                tempElement.AddNode(std::stoi(*it));

            tempElement.SetElementID(std::stoi(values[0]));
            m_Grid.AddElement(std::stoi(values[0]), tempElement);
        }
        else if (dataType == DataTypeEnum::BC)
        {
            std::vector<std::string> values = Split(line, ',');

            for (auto& value : values)
                m_Grid.SetNodeAsBoundaryCondition(std::stoi(value));
        }
		else if (dataType == DataTypeEnum::MATERIAL1)
		{
			std::vector<std::string> values = Split(line, ',');

            for (auto& value : values)
            {
                Parameters temp = {
                    m_GlobalData.GetAlpha(),
                    m_GlobalData.GetDensity(),
                    m_GlobalData.GetSpecificHeat(),
                    m_GlobalData.GetConductivity(),
                    m_GlobalData.GetTot()
                };

                m_Grid.SetParametersForElement(std::stoi(value), temp);
            }
		}
		else if (dataType == DataTypeEnum::MATERIAL2)
		{
			std::vector<std::string> values = Split(line, ',');

			for (auto& value : values)
			{
				Parameters temp = {
					m_GlobalData.GetAlpha_2(),
					m_GlobalData.GetDensity_2(),
					m_GlobalData.GetSpecificHeat_2(),
					m_GlobalData.GetConductivity_2(),
					m_GlobalData.GetTot_2()
				};

				m_Grid.SetParametersForElement(std::stoi(value), temp);
			}
		}
    }

    file.close();

    return { m_GlobalData, m_Grid };
}
