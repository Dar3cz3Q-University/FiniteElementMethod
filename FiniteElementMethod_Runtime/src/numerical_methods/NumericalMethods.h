#pragma once

#include "Matrix.h"

namespace NumericalMethods
{
	Matrix GaussElimination(const Matrix& L, const Matrix& U, const Matrix& B);
	void LUDecomposition(const Matrix& A, Matrix& L, Matrix& U);
};
