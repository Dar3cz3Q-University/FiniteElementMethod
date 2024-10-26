#pragma once

#include "Jacobian.h"
#include "Matrix.h"

class Derivatives
{
public:
    Derivatives();

public:
    void Calculate(const Jacobian& jacobian, int integrationPoint);

    const Matrix& GetXDerivatives() const { return m_Derivatives_X; }
    const Matrix& GetYDerivatives() const { return m_Derivatives_Y; }

private:
    Matrix m_Derivatives_X;
    Matrix m_Derivatives_Y;

public:
    friend std::ostream& operator<<(std::ostream& os, const Derivatives& derivatives);
};

std::ostream& operator<<(std::ostream& os, const Derivatives& derivatives);
