#include "Element.h"

Element::Element()
{
	m_Nodes.reserve(ELEMENT_NODES_SIZE);
}

inline void Element::AddNode(int nodeID)
{
	m_Nodes.push_back(nodeID);
}

std::ostream& operator<<(std::ostream& os, const Element& element)
{
	os << "{";

	for (auto it = element.m_Nodes.begin(); it != element.m_Nodes.end(); it++)
	{
		os << *it;
		if (std::next(it) != element.m_Nodes.end())
			os << ",";
	}

	os << "}";

	return os;
}
