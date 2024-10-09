#include "Grid.h"

Grid::Grid(int numberOfElements, int numberOfNodes)
{
    if (numberOfElements <= 0)
    {
        std::cerr << "Number of elements cannot be less than or equal to 0" << "\n";
        return;
    }
    
    if (numberOfNodes <= 0)
    {
        std::cerr << "Number of nodes cannot be less than or equal to 0" << "\n";
        return;
    }

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

inline void Grid::AddElement(Element element)
{
    m_Elements.push_back(element);
}

inline void Grid::AddNode(Node node)
{
    m_Nodes.push_back(node);
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    os << EnumToString(GlobalDataEnum::NODES_NUMBER) << " " << grid.GetNumberOfNodes() << "\n";
    os << EnumToString(GlobalDataEnum::ELEMENTS_NUMBER) << " " << grid.GetNumberOfElements() << "\n";

    os << "*Node" << "\n";

    int counter = 0;

    for (auto& node : grid.m_Nodes)
        os << counter++ << ", " << node << "\n";

    os << "*Element" << "\n";

    counter = 0;

    for (auto& element : grid.m_Elements)
        os << counter++ << ", " << element << "\n";

    return os;
}
