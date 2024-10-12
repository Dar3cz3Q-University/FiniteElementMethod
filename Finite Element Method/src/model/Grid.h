#pragma once

#include "Element.h"
#include "GlobalDataEnum.h"

#include <cstdint>
#include <iostream>

class Grid 
{
public:
	Grid() = default;
	Grid(int numberOfElements, int numberOfNodes);

public:
	size_t GetNumberOfNodes() const;
	size_t GetNumberOfElements() const;

	void ReserveElements(int numberOfElements) { m_Elements.reserve(numberOfElements); }
	void ReserveNodes(int numberOfNodes) { m_Nodes.reserve(numberOfNodes); }

	inline void AddElement(Element element) { m_Elements.push_back(element); }
	inline void AddNode(Node node) { m_Nodes.push_back(node); }

private:
	std::vector<Element> m_Elements;
	std::vector<Node> m_Nodes;

public:
	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

std::ostream& operator<<(std::ostream& os, const Grid& grid);
