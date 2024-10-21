#pragma once

#include "Derivatives.h"

constexpr auto JACOBIAN_DIMENSION = 2;

inline Derivatives DERIVATIVES;

class Jacobian
{
public:
	Jacobian();

public:
	void Calculate(const std::unordered_map<int, Node>& nodes, int numberOfIntegrationPoint);

private:
	void CalculateInverse();
	void CalculateDeterminant();

private:
	double m_JacobianMatrix[JACOBIAN_DIMENSION][JACOBIAN_DIMENSION];
	double m_InversedJacobianMatrix[JACOBIAN_DIMENSION][JACOBIAN_DIMENSION];
	double m_JacobianMatrixDeterminant;
};
