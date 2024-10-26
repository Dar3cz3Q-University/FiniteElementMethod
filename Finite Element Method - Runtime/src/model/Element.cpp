#include "pch.h"

#include "Element.h"

Element::Element()
{
	m_Nodes.reserve(ELEMENT_NODES_SIZE);

	m_Jacobians.reserve(INTEGRATION_POINTS_COUNT);
	m_Derivatives.reserve(INTEGRATION_POINTS_COUNT);
	m_H_Matricies.reserve(INTEGRATION_POINTS_COUNT);

	for (int i = 0; i < INTEGRATION_POINTS_COUNT; i++)
	{
		m_Jacobians.insert({ i + 1, Jacobian() });
		m_Derivatives.insert({ i + 1, Derivatives() });
		m_H_Matricies.insert({ i + 1, H_Matrix() });
	}
}

void Element::AddNode(int nodeID, Node node)
{
	// TODO: Nodes should not be stored twice
	// For now, nodes are stored twice. Once in Grid and second time in Element. It is because of calculating the Jacobian.
	// This should be changed in future
	m_Nodes.insert({nodeID, node});
}

Matrix Element::GetGlobalHMatrix()
{
	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	Matrix temp(4, 4);

	for (int i = 1; i <= INTEGRATION_POINTS_COUNT; i++)
		temp = temp + m_H_Matricies.at(i).GetMatrix() * INTEGRATION_WEIGHTS[i - 1].x * INTEGRATION_WEIGHTS[i - 1].y;
	
	return temp;
}

void Element::Calculate()
{
	// Order of running this methods is pretty important :)
	CalculateJacobians();
	CalculateDerivatives();
	CalculateHMatricies();
}

void Element::CalculateJacobians()
{
	for (auto& jacobian : m_Jacobians)
		jacobian.second.Calculate(m_Nodes, jacobian.first);
}

void Element::CalculateDerivatives()
{
	for (auto& derivative : m_Derivatives)
		derivative.second.Calculate(m_Jacobians.at(derivative.first), derivative.first);
}

void Element::CalculateHMatricies()
{
	// The value '30' should be changed to variable that is read from file
	for (auto& matrix : m_H_Matricies)
		matrix.second.Calculate(
			30,
			m_Jacobians.at(matrix.first).GetMatrixDeterminant(),
			m_Derivatives.at(matrix.first)
		);
}

void Element::DisplayCalculations()
{
	std::cout << "Element " << *this << "\n";

	for (auto& node : m_Nodes)
		std::cout << node.second << "\n";

	for (int i = 1; i <= INTEGRATION_POINTS_COUNT; i++)
	{
		std::cout << "---------------------------------------\n";
		std::cout << "Integration point: " << i << "\n";
		std::cout << m_Jacobians.at(i) << "\n";
		std::cout << "Derivatives\n";
		std::cout << m_Derivatives.at(i) << "\n";
		std::cout << "H Matrix" << "\n";
		std::cout << m_H_Matricies.at(i) << "\n";
	}

	std::cout << "Global H Matrix" << "\n";
	std::cout << GetGlobalHMatrix();
}

std::ostream& operator<<(std::ostream& os, const Element& element)
{
	os << "{";

	for (auto it = element.m_Nodes.begin(); it != element.m_Nodes.end(); it++)
	{
		os << (*it).first;
		if (std::next(it) != element.m_Nodes.end())
			os << ", ";
	}

	os << "}";

	return os;
}
