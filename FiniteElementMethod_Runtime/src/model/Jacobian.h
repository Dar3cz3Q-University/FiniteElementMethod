#pragma once

#include "IntegrationPointDerivatives.h"
#include "Matrix.h"

#include "gtest/gtest.h"

constexpr auto JACOBIAN_DIMENSION = 2;

class Jacobian
{
public:
	Jacobian();

public:
	void Calculate(const std::map<int, Node>& nodes, const std::vector<int>& nodesIDs, int integrationPoint);

	double GetMatrixAt(int x, int y) const { return m_JacobianMatrix.GetElement(x, y); };
	double GetInversedMatrixAt(int x, int y) const { return m_InversedJacobianMatrix.GetElement(x, y); };
	double GetMatrixDeterminant() const;

private:
	void CalculateMatrix(const std::map<int, Node>& nodes, const std::vector<int>& nodesIDs, int integrationPoint);
	void CalculateInverseMatrix();

private:
	Matrix m_JacobianMatrix;
	Matrix m_InversedJacobianMatrix;

public:
	friend std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian);

public:
	FRIEND_TEST(JacobianTest, GeneratesValidMatrixForFirstIntegrationPoint);
};

std::ostream& operator<<(std::ostream& os, const Jacobian& jacobian);
