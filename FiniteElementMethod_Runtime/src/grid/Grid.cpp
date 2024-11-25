#include "pch.h"

#include "Grid.h"

void Grid::GenerateNecessaryData(double conductivity, double alpha)
{
    LOG_TRACE("Generating simulation data (Jacobian, HMatrix)");

    // TODO: Multithreaded parts of the application are not working well with Google Test :(
#ifdef RUNNING_TEST

    ThreadPool* threadPool = ThreadPool::GetInstance();

    for (auto& element : m_Elements)
    {
        threadPool->QueueJob([&] {
            element.second.Calculate(m_Nodes, conductivity, alpha);
        });
    }

    threadPool->WaitAllJobs();

#else

    for (auto& element : m_Elements)
        element.second.Calculate(m_Nodes, conductivity, alpha);

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

    std::cout << m_GlobalHMatrix;
}

void Grid::GenerateGlobalHMatrix()
{
    LOG_TRACE("Generating global HMatrix");

    size_t numberOfNodes = m_Nodes.size();

    m_GlobalHMatrix = Matrix(numberOfNodes);

    for (size_t i = 0; i < numberOfNodes; i++) for (size_t j = 0; j < numberOfNodes; j++)
        m_GlobalHMatrix.SetElement(i, j, 0.0);

    for (auto& element : m_Elements)
        element.second.AddHMatrixToGlobalMatrix(m_Nodes, m_GlobalHMatrix);
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
