#pragma once

#include "Matrix.h"

namespace NumericalMethods
{
	std::pair<Matrix, Matrix> LUDecomposition(const Matrix& A);
	Matrix ForwardSubstitution(const Matrix& L, const Matrix& b);
	Matrix BackwardSubstitution(const Matrix& U, const Matrix& y);
	Matrix SolveGaussianLU(const Matrix& A, const Matrix& b);
};
