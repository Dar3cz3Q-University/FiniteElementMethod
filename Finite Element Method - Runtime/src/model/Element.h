#pragma once

#include "Node.h"

#define ELEMENT_NODES_SIZE 4

class Element 
{
public:
	Element();

public:
	inline void AddNode(int nodeID) { m_Nodes.push_back(nodeID); }

private:
	std::vector<int> m_Nodes;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
