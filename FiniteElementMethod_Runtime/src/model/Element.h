#pragma once

#include "Node.h"
#include "Jacobian.h"
#include "Derivatives.h"
#include "IntegrationPointDerivatives.h"
#include "H_Matrix.h"

constexpr auto ELEMENT_NODES_SIZE = 4;

class Element 
{
public:
	Element();

public:
	void AddNode(int nodeID, Node node);

	Matrix GetGlobalHMatrix();

	void Calculate();

	void DisplayCalculations();

private:
	void CalculateJacobians();
	void CalculateDerivatives();
	void CalculateHMatricies();

private:
	std::map<int, Node> m_Nodes;
	std::map<int, Jacobian> m_Jacobians;
	std::map<int, Derivatives> m_Derivatives;
	std::map<int, H_Matrix> m_H_Matricies;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
