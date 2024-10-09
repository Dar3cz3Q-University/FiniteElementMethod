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
	inline void AddElement(Element element);
	inline void AddNode(Node node);

private:
	std::vector<Element> m_Elements;
	std::vector<Node> m_Nodes;

public:
	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

std::ostream& operator<<(std::ostream& os, const Grid& grid);
