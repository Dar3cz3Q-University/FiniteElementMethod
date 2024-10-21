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
	auto& derivativesETA = DERIVATIVES.GetETADerivatives(numberOfIntegrationPoint);
	auto& derivativesKSI = DERIVATIVES.GetKSIDerivatives(numberOfIntegrationPoint);

	int numberOfIntegrationPoints = static_cast<int>(INTEGRATION_POINTS.size());

	for (int i = 0; i < numberOfIntegrationPoints; i++)
	{
		m_JacobianMatrix[0][0] += derivativesKSI.at(i) * nodes.at(i).x;
		m_JacobianMatrix[0][1] += derivativesKSI.at(i) * nodes.at(i).y;
		m_JacobianMatrix[1][0] += derivativesETA.at(i) * nodes.at(i).x;
		m_JacobianMatrix[1][1] += derivativesETA.at(i) * nodes.at(i).y;
	}

	CalculateDeterminant();
	CalculateInverse();
}

void Jacobian::CalculateInverse()
{

}

void Jacobian::CalculateDeterminant()
{

}

