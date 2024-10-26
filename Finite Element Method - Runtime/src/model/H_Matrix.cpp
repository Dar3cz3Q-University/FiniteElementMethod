#include "pch.h"

#include "H_Matrix.h"

H_Matrix::H_Matrix()
{}

void H_Matrix::Calculate(double alpha, double dV, const Derivatives& derivatives)
{
	Matrix normalX = derivatives.GetXDerivatives();
	Matrix transposedX = normalX.Transpose();

	Matrix x = transposedX * normalX;

	Matrix normalY = derivatives.GetYDerivatives();
	Matrix transposedY = normalY.Transpose();

	Matrix y = transposedY * normalY;

	Matrix result = x + y;

	result = result * alpha * dV;

	m_Data = result;
}

std::ostream& operator<<(std::ostream& os, const H_Matrix& matrix)
{
	os << matrix.m_Data;
	return os;
}
