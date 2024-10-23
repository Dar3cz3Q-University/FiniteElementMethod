#include "pch.h"

#include "Jacobian.h"

Jacobian::Jacobian()
{
	for (int i = 0; i < JACOBIAN_DIMENSION; i++) for (int j = 0; j < JACOBIAN_DIMENSION; j++)
	{
		m_JacobianMatrix[i][j] = 0.0;
		m_InversedJacobianMatrix[i][j] = 0.0;
	}
	m_JacobianMatrixDeterminant = 0.0;
}

void Jacobian::Calculate(const std::unordered_map<int, Node>& nodes, int numberOfIntegrationPoint)
{
	CalculateMatrix(nodes, numberOfIntegrationPoint);
	CalculateDeterminant();
	CalculateInverseMatrix();
}

void Jacobian::CalculateMatrix(const std::unordered_map<int, Node>& nodes, int numberOfIntegrationPoint)
{
	auto& derivativesETA = DERIVATIVES.GetETADerivatives(numberOfIntegrationPoint - 1);
	auto& derivativesKSI = DERIVATIVES.GetKSIDerivatives(numberOfIntegrationPoint - 1);

	int i = 0;

	for (auto& node : nodes)
	{
		m_JacobianMatrix[0][0] += derivativesKSI.at(i) * node.second.x;
		m_JacobianMatrix[0][1] += derivativesKSI.at(i) * node.second.y;
		m_JacobianMatrix[1][0] += derivativesETA.at(i) * node.second.x;
		m_JacobianMatrix[1][1] += derivativesETA.at(i) * node.second.y;
		i++;
	}
}

void Jacobian::CalculateInverseMatrix()
{
	double coefficent = 1.0 / m_JacobianMatrixDeterminant;

	m_InversedJacobianMatrix[0][0] = m_JacobianMatrix[1][1] * coefficent;
	m_InversedJacobianMatrix[0][1] = -m_JacobianMatrix[0][1] * coefficent;
	m_InversedJacobianMatrix[1][0] = -m_JacobianMatrix[1][0] * coefficent;
	m_InversedJacobianMatrix[1][1] = m_JacobianMatrix[1][1] * coefficent;
}

void Jacobian::CalculateDeterminant()
{
	// Currently only for JACOBIAN_DIMENSION = 2
	static_assert(JACOBIAN_DIMENSION == 2);

	m_JacobianMatrixDeterminant = m_JacobianMatrix[0][0] * m_JacobianMatrix[1][1] - (m_JacobianMatrix[0][1] * m_JacobianMatrix[1][0]);
}

std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian)
{
	const int PRECISION = 7;

	os << std::fixed << std::setprecision(PRECISION);

	os << "\nJacobian Matrix\n";
	os << jacobian.m_JacobianMatrix[0][0] << " | " << jacobian.m_JacobianMatrix[0][1] << "\n";
	os << jacobian.m_JacobianMatrix[1][0] << " | " << jacobian.m_JacobianMatrix[1][1] << "\n";
	os << "\nInversed Jacobian Matrix\n";
	os << jacobian.m_InversedJacobianMatrix[0][0] << " | " << jacobian.m_InversedJacobianMatrix[0][1] << "\n";
	os << jacobian.m_InversedJacobianMatrix[1][0] << " | " << jacobian.m_InversedJacobianMatrix[1][1] << "\n";
	os << "\nJacobian Matrix Determinant\n";
	os << "det[J] = " << jacobian.m_JacobianMatrixDeterminant << "\n";

	return os;
}
