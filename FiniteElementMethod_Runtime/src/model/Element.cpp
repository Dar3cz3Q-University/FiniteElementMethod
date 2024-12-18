#include "pch.h"

#include "Element.h"

Element::Element() 
	: m_ElementID(0.0), m_Vector_P(Matrix(1, ELEMENT_NODES_SIZE))
{
	LOG_TRACE("Initializing element variables");

	for (int i = 0; i < INTEGRATION_POINTS_COUNT; i++)
	{
		m_Jacobians.insert({ i + 1, Jacobian() });
		m_Derivatives.insert({ i + 1, Derivatives() });
		m_H_Matricies.insert({ i + 1, Matrix(ELEMENT_NODES_SIZE) });
		m_C_Matricies.insert({ i + 1, Matrix(ELEMENT_NODES_SIZE) });
	}

	m_NodesIDs.reserve(ELEMENT_NODES_SIZE);
}

void Element::Calculate(const std::map<int, Node>& nodes, const GlobalData& data)
{
	LOG_TRACE("Calculating data for {} element", m_ElementID);

	// Order of running this methods is pretty important :)
	CalculateJacobians(nodes);
	CalculateDerivatives();
	CalculateHMatricies(data.GetConductivity());
	CalculateCMatricies(data.GetDensity(), data.GetSpecificHeat());
	CalculateGlobalMatricies();
	CalculatePVector(nodes, data.GetAlpha(), data.GetTot());
	AddBoundaryHMatricies(nodes, data.GetAlpha());
}

void Element::AddHMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix) const
{
	LOG_TRACE("Adding {} element H matrix to global H matrix", m_ElementID);

	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, m_NodesIDs.at(j) - 1, m_Matrix_H.GetElement(i, j));
}

void Element::AddCMatrixToGlobalMatrix(const std::map<int, Node>& nodes, Matrix& matrix) const
{
	LOG_TRACE("Adding {} element C matrix to global C matrix", m_ElementID);

	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, m_NodesIDs.at(j) - 1, m_Matrix_C.GetElement(i, j));
}

void Element::AddPVectorToGlobalVector(const std::map<int, Node>& nodes, Matrix& matrix) const
{
	LOG_TRACE("Adding {} element C vector to global C vector", m_ElementID);

	for (int i = 0; i < 4; i++)
		matrix.AddToElement(m_NodesIDs.at(i) - 1, 0, m_Vector_P.GetElement(0, i));
}

void Element::CalculateJacobians(const std::map<int, Node>& nodes)
{
	for (auto& [key, jacobian] : m_Jacobians)
	{
		LOG_TRACE("Calculating Jacobian in {} integration point for {} element", key, m_ElementID);
		jacobian.Calculate(nodes, m_NodesIDs, key);

		LOG_TRACE("Displaying Jacobian in {} integration point for {} element", key, m_ElementID);
		std::cout << jacobian << "\n";
	}
}

void Element::CalculateDerivatives()
{
	for (auto& [key, derivative] : m_Derivatives)
	{
		LOG_TRACE("Calculating derivatives in {} integration point for {} element", key, m_ElementID);
		derivative.Calculate(m_Jacobians.at(key), key);

		LOG_TRACE("Displaying derivatives in {} integration point for {} element", key, m_ElementID);
		std::cout << derivative << "\n";
	}
}

void Element::CalculateHMatricies(double conductivity)
{
	for (auto& [key, matrix] : m_H_Matricies)
	{
		LOG_TRACE("Calculating H matrix in {} integration point for {} element", key, m_ElementID);

		double dV = m_Jacobians.at(key).GetMatrixDeterminant();

		Matrix normalX = m_Derivatives.at(key).GetXDerivatives();
		Matrix transposedX = normalX.Transpose();

		Matrix x = transposedX * normalX;

		Matrix normalY = m_Derivatives.at(key).GetYDerivatives();
		Matrix transposedY = normalY.Transpose();

		Matrix y = transposedY * normalY;

		matrix = x + y;

		matrix = matrix * conductivity * dV;

		LOG_TRACE("Displaying H matrix in {} integration point for {} element", key, m_ElementID);
		std::cout << matrix << "\n";
	}
}

void Element::CalculateCMatricies(double density, double specificHeat)
{
	std::vector<Matrix> universalCMatricies = UniversalElement::GetInstance()->GetCMatricies();

	for (auto& [key, matrix] : m_C_Matricies)
	{
		LOG_TRACE("Calculating C matrix in {} integration point for {} element", key, m_ElementID);

		double dV = m_Jacobians.at(key).GetMatrixDeterminant();
		matrix = universalCMatricies.at(key - 1) * density * specificHeat * dV;

		LOG_TRACE("Displaying C matrix in {} integration point for {} element", key, m_ElementID);
		std::cout << matrix << "\n";
	}
}

void Element::AddBoundaryHMatricies(const std::map<int, Node>& nodes, double alpha)
{
	LOG_TRACE("Adding boundary H matrix to {} element global H matrix", m_ElementID);

	UniversalElement* surfaces = UniversalElement::GetInstance();

	for (int i = 0; i < 4; i++)
	{
		Node p1 = nodes.at(m_NodesIDs.at(i));
		Node p2 = nodes.at(m_NodesIDs.at((i + 1) % 4));

		if (p1.IsBoundaryCondition && p2.IsBoundaryCondition)
		{
			Matrix tempMatrix = surfaces->GetSurfaceMatrixForDirection((SurfaceEnum)i);
			double dx = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
			double detJ = dx / 2.0;

			m_Matrix_H = m_Matrix_H + (tempMatrix * detJ * alpha);
		}
	}

	LOG_TRACE("Displaying global H matrix with boundary condition for {} element", m_ElementID);
	std::cout << m_Matrix_H;
}

void Element::CalculateGlobalMatricies()
{
	LOG_TRACE("Calculating global H and C matrix for {} element", m_ElementID);

	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	Matrix temp_H(4);
	Matrix temp_C(4);

	for (int i = 1; i <= INTEGRATION_POINTS_COUNT; i++)
	{
		temp_H = temp_H + m_H_Matricies.at(i) * derivatives->GetIntegrationWeight(i - 1).x * derivatives->GetIntegrationWeight(i - 1).y;
		temp_C = temp_C + m_C_Matricies.at(i) * derivatives->GetIntegrationWeight(i - 1).x * derivatives->GetIntegrationWeight(i - 1).y;
	}

	LOG_TRACE("Displaying global H matrix for {} element", m_ElementID);
	std::cout << temp_H << "\n";

	LOG_TRACE("Displaying global C matrix for {} element", m_ElementID);
	std::cout << temp_C << "\n";

	m_Matrix_H = temp_H;
	m_Matrix_C = temp_C;
}

void Element::CalculatePVector(const std::map<int, Node>& nodes, double alpha, double ambientTemperature)
{
	LOG_TRACE("Calculating global P vector for {} element", m_ElementID);

	UniversalElement* surfaces = UniversalElement::GetInstance();

	for (int i = 0; i < 4; i++)
	{
		Node p1 = nodes.at(m_NodesIDs.at(i));
		Node p2 = nodes.at(m_NodesIDs.at((i + 1) % 4));

		if (p1.IsBoundaryCondition && p2.IsBoundaryCondition)
		{
			Matrix tempMatrix = surfaces->GetSurfaceVectorForDirection((SurfaceEnum)i);
			double dx = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
			double detJ = dx / 2.0;

			m_Vector_P = m_Vector_P + (tempMatrix.Transpose() * detJ * alpha * ambientTemperature);
		}
	}

	LOG_TRACE("Displaying global P vector for {} element", m_ElementID);
	std::cout << m_Vector_P;
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
