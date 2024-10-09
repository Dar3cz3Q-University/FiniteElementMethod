#pragma once

#include "Node.h"

#include <memory>
#include <vector>

#define ELEMENT_NODES_SIZE 4

class Element 
{
public:
	Element();

public:
	inline void AddNode(int nodeID);

private:
	std::vector<int> m_Nodes;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
