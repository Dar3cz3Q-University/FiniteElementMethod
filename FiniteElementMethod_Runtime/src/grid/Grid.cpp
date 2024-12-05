#include "pch.h"

#include "Grid.h"

void Grid::GenerateNecessaryData(double conductivity, double alpha, double ambientTemperature)
{
    LOG_TRACE("Generating simulation data (Jacobian, HMatrix)");

    // TODO: Multithreaded parts of the application are not working well with Google Test :(
#ifndef RUNNING_TEST

    ThreadPool* threadPool = ThreadPool::GetInstance();

    for (auto& element : m_Elements)
    {
        threadPool->QueueJob([&] {
            element.second.Calculate(m_Nodes, conductivity, alpha, ambientTemperature);
        });
    }

    threadPool->WaitAllJobs();

#else

    for (auto& element : m_Elements)
        element.second.Calculate(m_Nodes, conductivity, alpha, ambientTemperature);

#endif

    GenerateGlobalHMatrix();
}

void Grid::DisplayAllCalculatedData()
{
    LOG_TRACE("Displaying debug data");

    for (auto& element : m_Elements)
    {
        std::cout << "Calculated values for " << element.first << " element:\n";
        element.second.DisplayCalculations();
        std::cout << "\n";
    }

    std::cout << "Global H matrix\n";
    std::cout << m_GlobalHMatrix;

    std::cout << "Global P vector\n";
    std::cout << m_GlobalPVector;
}

void Grid::GenerateGlobalHMatrix()
{
    LOG_TRACE("Generating global HMatrix and global PVector");

    size_t numberOfNodes = m_Nodes.size();

    m_GlobalHMatrix = Matrix(numberOfNodes);
    for (size_t i = 0; i < numberOfNodes; i++) for (size_t j = 0; j < numberOfNodes; j++)
        m_GlobalHMatrix.SetElement(i, j, 0.0);

    m_GlobalPVector = Matrix(1, numberOfNodes);
    for (size_t i = 0; i < numberOfNodes; i++)
        m_GlobalPVector.SetElement(i, 0, 0.0);

    std::cout << m_GlobalPVector << "\n";

    for (auto& element : m_Elements)
    {
        element.second.AddHMatrixToGlobalMatrix(m_Nodes, m_GlobalHMatrix);
        element.second.AddPVectorToGlobalVector(m_Nodes, m_GlobalPVector);
    }
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    os << EnumToString(GlobalDataEnum::NODES_NUMBER) << " " << grid.GetNumberOfNodes() << "\n";
    os << EnumToString(GlobalDataEnum::ELEMENTS_NUMBER) << " " << grid.GetNumberOfElements() << "\n";

    os << "*Node" << "\n";

    for (auto& node : grid.m_Nodes)
        os << "\t" << node.first << ", " << node.second << "\n";

    os << "*Element" << "\n";

    for (auto& element : grid.m_Elements)
        os << "\t" << element.first << ", " << element.second << "\n";

    return os;
}
