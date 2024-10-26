#pragma once

#include "Matrix.h"
#include "Jacobian.h"
#include "Derivatives.h"

class H_Matrix
{
public:
	H_Matrix();

public:
	void Calculate(double alpha, double dV, const Derivatives& derivatives);

	Matrix GetMatrix() const { return m_Data; };

private:
	Matrix m_Data;

public:
	friend std::ostream& operator<<(std::ostream& os, const H_Matrix& matrix);
};

std::ostream& operator<<(std::ostream& os, const H_Matrix& matrix);
