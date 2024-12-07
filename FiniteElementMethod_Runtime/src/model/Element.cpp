#include "pch.h"

#include "Element.h"

Element::Element() : 
	m_ElementID(0.0), m_GlobalPVector(Matrix(4, 1))
{
	for (int i = 0; i < INTEGRATION_POINTS_COUNT; i++)
	{
		m_Jacobians.insert({ i + 1, Jacobian() });
		m_Derivatives.insert({ i + 1, Derivatives() });
		m_H_Matricies.insert({ i + 1, H_Matrix() });
	}
	m_NodesIDs.reserve(4);
}

void Element::Calculate(const std::map<int, Node>& nodes, double conductivity, double alpha, double ambientTemperature)
{
	LOG_TRACE("Calculating data for {} element", m_ElementID);

	// Order of running this methods is pretty important :)
	CalculateJacobians(nodes);
	CalculateDerivatives();
	CalculateHMatricies(conductivity);
	CalculateGlobalHMatrix();
	CalculatePVector(nodes, alpha, ambientTemperature);

	AddBoundaryHMatricies(nodes, alpha);
}

void Element::AddHMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix) const
{
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, m_NodesIDs.at(j) - 1, m_GlobalHMatrix.GetElement(i, j));
}

void Element::AddPVectorToGlobalVector(const std::map<int, Node>& nodes, Matrix& matrix) const
{
	for (int i = 0; i < 4; i++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, 0, m_GlobalPVector.GetElement(0, i));
}

void Element::CalculateJacobians(const std::map<int, Node>& nodes)
{
	for (auto& [key, jacobian] : m_Jacobians)
		jacobian.Calculate(nodes, m_NodesIDs, key);
}

void Element::CalculateDerivatives()
{
	for (auto& [key, derivative] : m_Derivatives)
		derivative.Calculate(m_Jacobians.at(key), key);
}

void Element::CalculateHMatricies(double conductivity)
{
	for (auto& [key, matrix] : m_H_Matricies)
		matrix.Calculate(
			conductivity,
			m_Jacobians.at(key).GetMatrixDeterminant(),
			m_Derivatives.at(key)
		);
}

void Element::AddBoundaryHMatricies(const std::map<int, Node>& nodes, double alpha)
{
	Surface* surfaces = Surface::GetInstance();

	for (int i = 0; i < 4; i++)
	{
		Node p1 = nodes.at(m_NodesIDs.at(i));
		Node p2 = nodes.at(m_NodesIDs.at((i + 1) % 4));

		if (p1.IsBoundaryCondition && p2.IsBoundaryCondition)
		{
			Matrix tempMatrix = surfaces->GetSurfaceMatrixForDirection((SurfaceEnum)i);
			double dx = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
			double detJ = dx / 2.0;

			m_GlobalHMatrix = m_GlobalHMatrix + (tempMatrix * detJ * alpha);
		}
	}
}

void Element::CalculateGlobalHMatrix()
{
	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	Matrix temp(4, 4);

	for (int i = 1; i <= INTEGRATION_POINTS_COUNT; i++)
		temp = temp + m_H_Matricies.at(i).GetMatrix() * derivatives->GetIntegrationWeight(i - 1).x * derivatives->GetIntegrationWeight(i - 1).y;

	m_GlobalHMatrix = temp;
}

void Element::CalculatePVector(const std::map<int, Node>& nodes, double alpha, double ambientTemperature)
{
	Surface* surfaces = Surface::GetInstance();

	for (int i = 0; i < 4; i++)
	{
		Node p1 = nodes.at(m_NodesIDs.at(i));
		Node p2 = nodes.at(m_NodesIDs.at((i + 1) % 4));

		if (p1.IsBoundaryCondition && p2.IsBoundaryCondition)
		{
			Matrix tempMatrix = surfaces->GetSurfaceVectorForDirection((SurfaceEnum)i);
			double dx = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
			double detJ = dx / 2.0;

			m_GlobalPVector = m_GlobalPVector + (tempMatrix * detJ * alpha * ambientTemperature);
		}
	}
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
