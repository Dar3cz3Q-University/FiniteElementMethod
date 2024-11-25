#pragma once

#include "Node.h"
#include "Jacobian.h"
#include "Derivatives.h"
#include "IntegrationPointDerivatives.h"
#include "H_Matrix.h"
#include "Surface.h"
#include "SurfaceEnum.h"

constexpr auto ELEMENT_NODES_SIZE = 4;

class Element 
{
public:
	Element();

public:
	inline void SetElementID(int elementID) { m_ElementID = elementID; }
	inline void AddNode(int nodeID) { m_NodesIDs.emplace_back(nodeID); }

	void Calculate(const std::map<int, Node>& nodes, double conductivity, double alpha);
	void AddHMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix);

	void DisplayCalculations();

	inline Matrix GetGlobalHMatrix() const { return m_GlobalHMatrix; }

private:
	void CalculateJacobians(const std::map<int, Node>& nodes);
	void CalculateDerivatives();
	void CalculateHMatricies(double conductivity);
	void AddBoundaryHMatricies(const std::map<int, Node>& nodes);
	void CalculateGlobalHMatrix();

private:
	int m_ElementID;
	std::vector<int> m_NodesIDs;
	std::map<int, Jacobian> m_Jacobians;
	std::map<int, Derivatives> m_Derivatives;
	std::map<int, H_Matrix> m_H_Matricies;
	Matrix m_GlobalHMatrix;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
