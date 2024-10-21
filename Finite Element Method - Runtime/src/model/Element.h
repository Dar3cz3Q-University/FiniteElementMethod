#pragma once

#include "Node.h"
#include "Jacobian.h"

constexpr auto ELEMENT_NODES_SIZE = 4;

class Grid;

class Element 
{
public:
	Element();

public:
	void AddNode(int nodeID, Node node);
	void CalculateJacobian();

private:
	std::unordered_map<int, Node> m_Nodes;
	std::vector<Jacobian> m_Jacobians;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
