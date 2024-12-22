#include "pch.h"

#include "Grid.h"

void Grid::Calculate(const GlobalData& data)
{
    // TODO: Multithreaded parts of the application are not working well with Google Test :(
#ifndef RUNNING_TEST

    LOG_TRACE("Calculating elements in parallel mode");
    LOG_WARN("Displayed data can make no sense. Printing is not prepared for parallel yet ;) \n For better data analysing use 1 thread");

    ThreadPool* threadPool = ThreadPool::GetInstance();

    for (auto& element : m_Elements)
    {
        threadPool->QueueJob([&] {
            element.second.Calculate(m_Nodes, data);
        });
    }

    threadPool->WaitAllJobs();

#else

    LOG_TRACE("Calculating elements in sequential mode");

    for (auto& [key, element] : m_Elements)
        element.Calculate(m_Nodes, data);

#endif

    LOG_TRACE("Calculating global grid data");

    CalculateGlobalData();
}

void Grid::CalculateGlobalData()
{
    LOG_TRACE("Initializing global H, C matrix and P vector");

    size_t numberOfNodes = GetNumberOfNodes();

    m_Matrix_H = Matrix(numberOfNodes);
    m_Matrix_C = Matrix(numberOfNodes);
    m_Vector_P = Matrix(numberOfNodes, 1);

    for (size_t i = 0; i < numberOfNodes; i++)
    {
        m_Vector_P.SetElement(i, 0, 0.0);
        for (size_t j = 0; j < numberOfNodes; j++)
        {
            m_Matrix_H.SetElement(i, j, 0.0);
            m_Matrix_C.SetElement(i, j, 0.0);
        }
    }

    LOG_TRACE("Calculating global H, C matrix and P vector");

    for (auto& [_, element] : m_Elements)
    {
        element.AddHMatrixToGlobalMatrix(m_Nodes, m_Matrix_H);
        element.AddCMatrixToGlobalMatrix(m_Nodes, m_Matrix_C);
        element.AddPVectorToGlobalVector(m_Nodes, m_Vector_P);
    }

    LOG_TRACE("Displaying global H matrix");
    std::cout << m_Matrix_H << "\n";

    LOG_TRACE("Displaying global C matrix");
    std::cout << m_Matrix_C << "\n";

    LOG_TRACE("Displaying global P vector");
    std::cout << m_Vector_P << "\n";
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    os << EnumToString(GlobalDataEnum::NODES_NUMBER) << " " << grid.GetNumberOfNodes() << "\n";
    os << EnumToString(GlobalDataEnum::ELEMENTS_NUMBER) << " " << grid.GetNumberOfElements() << "\n";

    os << "*Node" << "\n";

    for (auto& [key, node] : grid.m_Nodes)
        os << "\t" << key << ", " << node << "\n";

    os << "*Element" << "\n";

    for (auto& [key, element] : grid.m_Elements)
        os << "\t" << key << ", " << element << "\n";

    return os;
}
