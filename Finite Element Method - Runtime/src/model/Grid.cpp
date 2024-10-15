#include "pch.h"

#include "Grid.h"

Grid::Grid(int numberOfElements, int numberOfNodes)
{
    if (numberOfElements <= 0)
        throw std::invalid_argument("Number of elements cannot be less than or equal to 0");
    
    if (numberOfNodes <= 0)
        throw std::invalid_argument("Number of nodes cannot be less than or equal to 0");

    m_Elements.reserve(numberOfElements);
    m_Nodes.reserve(numberOfNodes);
}

size_t Grid::GetNumberOfNodes() const
{
    return m_Nodes.size();
}

size_t Grid::GetNumberOfElements() const
{
    return m_Elements.size();
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
