#pragma once

#include "FileReader.h"
#include "DataTypeEnum.h"
#include "GlobalDataEnum.h"
#include "StringUtils.h"

class TXTFileReader : public FileReader
{
public:
	TXTFileReader();

public:
	const std::string& GetFileType() const override;
	GlobalData Read(const std::filesystem::path& path) override;

private:
	std::string m_ReaderName;
	GlobalData m_GlobalData;

	std::unordered_map<GlobalDataEnum, std::function<void(const std::string&)>> m_GlobalDataVariableSetters = {
        { GlobalDataEnum::SIMULATION_TIME, [&](const std::string& value) { m_GlobalData.SetSimulationTime(std::stoi(value)); }},
        { GlobalDataEnum::SIMULATION_STEP_TIME, [&](const std::string& value) { m_GlobalData.SetSimulationStepTime(std::stoi(value)); }},
        { GlobalDataEnum::CONDUCTIVITY, [&](const std::string& value) { m_GlobalData.SetConductivity(std::stod(value)); }},
        { GlobalDataEnum::ALPHA, [&](const std::string& value) { m_GlobalData.SetAlpha(std::stod(value)); }},
        { GlobalDataEnum::TOT, [&](const std::string& value) { m_GlobalData.SetTot(std::stod(value)); }},
        { GlobalDataEnum::INITIAL_TEMP, [&](const std::string& value) { m_GlobalData.SetInitialTemp(std::stod(value)); }},
        { GlobalDataEnum::DENSITY, [&](const std::string& value) { m_GlobalData.SetDensity(std::stod(value)); }},
        { GlobalDataEnum::SPECIFIC_HEAT, [&](const std::string& value) { m_GlobalData.SetSpecificHeat(std::stod(value)); }},
        { GlobalDataEnum::ELEMENTS_NUMBER, [&](const std::string& value) { m_GlobalData.ReserveGridElements(std::stoi(value)); }},
        { GlobalDataEnum::NODES_NUMBER, [&](const std::string& value) { m_GlobalData.ReserveGridNodes(std::stod(value)); }}
    };
};

