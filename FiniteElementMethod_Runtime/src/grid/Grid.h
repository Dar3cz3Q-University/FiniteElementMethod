#pragma once

#include "Element.h"
#include "GlobalDataEnum.h"
#include "multithreading/ThreadPool.h"

class Grid 
{
public:
	Grid() = default;
	Grid(int numberOfElements, int numberOfNodes);

public:
	void GenerateNecessaryData();

public:
	size_t GetNumberOfNodes() const { return m_Nodes.size(); };
	size_t GetNumberOfElements() const { return m_Elements.size(); };

	Node GetNode(int index) const { return m_Nodes.at(index); }

	inline void AddElement(int index, Element element) { m_Elements.insert({ index, element }); }
	inline void AddNode(int index, Node node) { m_Nodes.insert({ index, node }); }

private:
	std::map<int, Element> m_Elements;
	std::map<int, Node> m_Nodes;

private:
	void DisplayDebugData();

public:
	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

std::ostream& operator<<(std::ostream& os, const Grid& grid);
