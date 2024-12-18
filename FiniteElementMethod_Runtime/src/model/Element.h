#pragma once

#include "Node.h"
#include "Jacobian.h"
#include "Derivatives.h"
#include "IntegrationPointDerivatives.h"
#include "UniversalElement.h"
#include "SurfaceEnum.h"
#include "GlobalData.h"

constexpr auto ELEMENT_NODES_SIZE = 4;

class Element 
{
public:
	Element();

public:
	inline void SetElementID(int elementID) { m_ElementID = elementID; }
	inline void AddNode(int nodeID) { m_NodesIDs.emplace_back(nodeID); }

	void Calculate(const std::map<int, Node>& nodes, const GlobalData& data);
	void AddHMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix) const;
	void AddCMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix) const;
	void AddPVectorToGlobalVector(const std::map<int, Node>& nodes, Matrix& matrix) const;

private:
	void CalculateJacobians(const std::map<int, Node>& nodes);
	void CalculateDerivatives();
	void CalculateHMatricies(double conductivity);
	void CalculateCMatricies(double density, double specificHeat);
	void CalculateGlobalMatricies();
	void CalculatePVector(const std::map<int, Node>& nodes, double alpha, double ambientTemperature);

	void AddBoundaryHMatricies(const std::map<int, Node>& nodes, double alpha);

private:
	int m_ElementID;
	std::vector<int> m_NodesIDs;
	std::map<int, Jacobian> m_Jacobians;
	std::map<int, Derivatives> m_Derivatives;
	std::map<int, Matrix> m_H_Matricies;
	std::map<int, Matrix> m_C_Matricies;
	Matrix m_Matrix_H;
	Matrix m_Matrix_C;
	Matrix m_Vector_P;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const Element& element);
};

std::ostream& operator<<(std::ostream& os, const Element& element);
