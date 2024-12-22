#include "pch.h"
#include "VTKFileWriter.h"

std::filesystem::path VTKFileWriter::s_Folder;
int VTKFileWriter::s_Step = 0;

VTKFileWriter::VTKFileWriter()
{
	GenerateFolder();
}

void VTKFileWriter::GenerateFolder()
{
	if (!std::filesystem::exists(RESULTS_FOLDER_PATH)) std::filesystem::create_directory(RESULTS_FOLDER_PATH);

	if (std::filesystem::exists(s_Folder)) return;

	std::filesystem::path workingDir = std::filesystem::current_path();

	std::time_t rawTime;
	struct tm result;
	time(&rawTime);

#ifdef _WIN32
	localtime_s(&result, &rawTime);
#else
	localtime_r(&rawTime, &result);
#endif

	std::ostringstream newFolderName;
	newFolderName << std::put_time(&result, "%Y-%m-%d_%H-%M-%S");

	s_Folder = workingDir / RESULTS_FOLDER_PATH / newFolderName.str();

	LOG_INFO("Generating results folder: '{}'", s_Folder.string());

	std::filesystem::create_directory(s_Folder);
}

void VTKFileWriter::AddHeader(std::ofstream& file)
{
	file << "# vtk DataFile Version 5.13\n";
}

// TODO: For now we save the mesh in every file. It should be saved in base.vtk and in time_x.vtk should be only temperatures

void VTKFileWriter::SaveMesh(const Grid& grid)
{
	std::stringstream universalData;

	universalData.precision(PRECISION);

	universalData << "# vtk DataFile Version 4.6\n";

	universalData << "Base mesh\n";
	universalData << "ASCII\n";
	universalData << "DATASET UNSTRUCTURED_GRID\n";
	universalData << "POINTS " << grid.GetNumberOfNodes() << " float\n";

	for (auto& [_, node] : grid.m_Nodes)
		universalData << node.x << " " << node.y << " " << "0.0" << "\n";

	universalData << "CELLS " << grid.GetNumberOfElements() << " " << grid.GetNumberOfElements() * (ELEMENT_NODES_SIZE + 1) << "\n";

	for (auto& [_, element] : grid.m_Elements)
	{
		universalData << ELEMENT_NODES_SIZE << " ";
		auto nodesIDs = element.GetNodesIDs();

		for (auto id : nodesIDs)
			universalData << id - 1 << " ";

		universalData << "\n";
	}

	universalData << "CELL_TYPES " << grid.GetNumberOfElements() << "\n";

	for (auto& [key, _] : grid.m_Elements)
		universalData << 9 << "\n"; // TODO: Move 9 to a variable. This is a code of type of the element in the VTK format

	m_UniversalData = universalData.str();
}

void VTKFileWriter::SaveTemperatureInTime(const Matrix& matrix)
{
	std::string fileName = "time_" + std::to_string(s_Step++) + ".vtk";
	std::ofstream file(s_Folder / fileName);

	file << m_UniversalData;

	file << "POINT_DATA " << matrix.GetHeight() << "\n";
	file << "SCALARS temperature float 1\n";
	file << "LOOKUP_TABLE default\n";

	file << matrix << "\n";

	file.close();
}

