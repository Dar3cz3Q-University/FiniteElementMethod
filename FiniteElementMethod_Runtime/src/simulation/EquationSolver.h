#pragma once

#include "Matrix.h"
#include "GlobalData.h"
#include "numerical_methods/NumericalMethods.h"

class EquationSolver
{
public:
	EquationSolver(const GlobalData& data, const Matrix& H, const Matrix& C, const Matrix& P);

	void Run();

private:
	GlobalData m_GlobalData;
	Matrix m_Matrix_A;
	Matrix m_Matrix_C;
	Matrix m_Vector_P;
	Matrix m_Vector_T;
	double m_dT_Coef;
};

