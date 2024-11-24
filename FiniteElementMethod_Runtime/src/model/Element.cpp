#include "pch.h"

#include "Element.h"

Element::Element()
{
	for (int i = 0; i < INTEGRATION_POINTS_COUNT; i++)
	{
		m_Jacobians.insert({ i + 1, Jacobian() });
		m_Derivatives.insert({ i + 1, Derivatives() });
		m_H_Matricies.insert({ i + 1, H_Matrix() });
	}
	m_NodesIDs.reserve(4);
}

void Element::Calculate(int elementID, const std::map<int, Node>& nodes, double conductivity, double alpha)
{
	LOG_TRACE("Calculating data for {} element", elementID);

	// Order of running this methods is pretty important :)
	CalculateJacobians(nodes);
	CalculateDerivatives();
	CalculateHMatricies(alpha);
	// Calculate HBC matricies and add them to H matricies
	CalculateGlobalHMatrix();
}

void Element::AddHMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix)
{
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, m_NodesIDs.at(j) - 1, m_GlobalHMatrix.GetElement(i, j));
}

void Element::CalculateJacobians(const std::map<int, Node>& nodes)
{
	for (auto& jacobian : m_Jacobians)
		jacobian.second.Calculate(nodes, m_NodesIDs, jacobian.first);
}

void Element::CalculateDerivatives()
{
	for (auto& derivative : m_Derivatives)
		derivative.second.Calculate(m_Jacobians.at(derivative.first), derivative.first);
}

void Element::CalculateHMatricies(double conductivity)
{
	for (auto& matrix : m_H_Matricies)
		matrix.second.Calculate(
			conductivity,
			m_Jacobians.at(matrix.first).GetMatrixDeterminant(),
			m_Derivatives.at(matrix.first)
		);
}

void Element::CalculateGlobalHMatrix()
{
	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	Matrix temp(4, 4);

	for (int i = 1; i <= INTEGRATION_POINTS_COUNT; i++)
		temp = temp + m_H_Matricies.at(i).GetMatrix() * derivatives->GetIntegrationWeight(i - 1).x * derivatives->GetIntegrationWeight(i - 1).y;

	m_GlobalHMatrix = temp;
}

void Element::DisplayCalculations()
{
	std::cout << "Element " << *this << "\n";

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

	for (auto it = element.m_NodesIDs.begin(); it != element.m_NodesIDs.end(); it++)
	{
		os << (*it);
		if (std::next(it) != element.m_NodesIDs.end())
			os << ", ";
	}

	os << "}";

	return os;
}
