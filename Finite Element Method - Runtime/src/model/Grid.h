#pragma once

#include "Element.h"
#include "GlobalDataEnum.h"

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

	inline void AddElement(int index, Element element) { m_Elements.insert({ index, element }); }
	inline void AddNode(int index, Node node) { m_Nodes.insert({ index, node }); }

private:
	std::unordered_map<int, Element> m_Elements;
	std::unordered_map<int, Node> m_Nodes;

public:
	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

std::ostream& operator<<(std::ostream& os, const Grid& grid);
