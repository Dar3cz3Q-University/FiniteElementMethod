#include "pch.h"

#include "Jacobian.h"

Jacobian::Jacobian()
	: m_JacobianMatrix(Matrix(JACOBIAN_DIMENSION, JACOBIAN_DIMENSION)), m_InversedJacobianMatrix(Matrix(JACOBIAN_DIMENSION, JACOBIAN_DIMENSION))
{
	for (int i = 0; i < JACOBIAN_DIMENSION; i++) for (int j = 0; j < JACOBIAN_DIMENSION; j++)
	{
		m_JacobianMatrix.SetElement(i, j, 0.0);
		m_InversedJacobianMatrix.SetElement(i, j, 0.0);
	}
}

void Jacobian::Calculate(const std::map<int, Node>& nodes, const std::vector<int>& nodesIDs, int integrationPoint)
{
	CalculateMatrix(nodes, nodesIDs, integrationPoint);
	CalculateInverseMatrix();
}

double Jacobian::GetMatrixDeterminant() const
{
	return m_JacobianMatrix.GetDeterminant();
}

void Jacobian::CalculateMatrix(const std::map<int, Node>& nodes, const std::vector<int>& nodesIDs, int integrationPoint)
{
	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	auto& derivativesETA = derivatives->GetETADerivatives(integrationPoint);
	auto& derivativesKSI = derivatives->GetKSIDerivatives(integrationPoint);

	int i = 0;

	double dX_dKsi = 0.0, dY_dKsi = 0.0, dX_dEta = 0.0, dY_dEta = 0.0;

	for (auto& node : nodesIDs)
	{
		dX_dKsi += derivativesKSI.at(i) * nodes.at(node).x;
		dY_dKsi += derivativesKSI.at(i) * nodes.at(node).y;
		dX_dEta += derivativesETA.at(i) * nodes.at(node).x;
		dY_dEta += derivativesETA.at(i) * nodes.at(node).y;
		i++;
	}

	m_JacobianMatrix.SetElement(0, 0, dX_dKsi);
	m_JacobianMatrix.SetElement(0, 1, dY_dKsi);
	m_JacobianMatrix.SetElement(1, 0, dX_dEta);
	m_JacobianMatrix.SetElement(1, 1, dY_dEta);
}

void Jacobian::CalculateInverseMatrix()
{
	double coefficent = 1.0 / m_JacobianMatrix.GetDeterminant();

	m_InversedJacobianMatrix.SetElement(0, 0, m_JacobianMatrix.GetElement(1, 1) * coefficent);
	m_InversedJacobianMatrix.SetElement(0, 1, -m_JacobianMatrix.GetElement(0, 1) * coefficent);
	m_InversedJacobianMatrix.SetElement(1, 0, -m_JacobianMatrix.GetElement(1, 0) * coefficent);
	m_InversedJacobianMatrix.SetElement(1, 1, m_JacobianMatrix.GetElement(0, 0) * coefficent);
}

std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian)
{
	os << std::fixed << std::setprecision(PRINT_PRECISION);

	os << "\nJacobian Matrix\n";
	os << jacobian.m_JacobianMatrix.GetElement(0, 0) << " | " << jacobian.m_JacobianMatrix.GetElement(0, 1) << "\n";
	os << jacobian.m_JacobianMatrix.GetElement(1, 0) << " | " << jacobian.m_JacobianMatrix.GetElement(1, 1) << "\n";

	os << "\nInversed Jacobian Matrix\n";
	os << jacobian.m_InversedJacobianMatrix.GetElement(0, 0) << " | " << jacobian.m_InversedJacobianMatrix.GetElement(0, 1) << "\n";
	os << jacobian.m_InversedJacobianMatrix.GetElement(1, 0) << " | " << jacobian.m_InversedJacobianMatrix.GetElement(1, 1) << "\n";

	os << "\nJacobian Matrix Determinant\n";
	os << "det[J] = " << jacobian.m_JacobianMatrix.GetDeterminant() << "\n";

	return os;
}
