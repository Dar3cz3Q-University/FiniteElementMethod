#pragma once

#include "Grid.h"
#include "Log.h"

// TODO: Add macro to add ability to disable saving to file

auto constexpr PRECISION = 4;
auto constexpr RESULTS_FOLDER_PATH = "..\\Results";

class VTKFileWriter
{
public:
	void SaveMesh(const Grid& grid);
	void SaveTemperatureInTime(const Matrix& matrix);

public:
	static VTKFileWriter& GetInstance()
	{
		static VTKFileWriter s_Instance;
		return s_Instance;
	}

public:
	VTKFileWriter();
	VTKFileWriter(const VTKFileWriter&) = delete;
	VTKFileWriter& operator=(const VTKFileWriter&) = delete;

private:
	static void GenerateFolder();
	void AddHeader(std::ofstream& file);

private:
	static std::filesystem::path s_Folder;
	static int s_Step;
	std::string m_UniversalData;
};
