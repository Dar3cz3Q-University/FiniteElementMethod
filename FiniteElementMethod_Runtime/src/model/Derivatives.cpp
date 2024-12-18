#include "pch.h"

#include "Derivatives.h"
#include "IntegrationPointDerivatives.h"
#include "GlobalData.h"
#include "Grid.h"

Derivatives::Derivatives()
    : m_Derivatives_X(Matrix(1, ELEMENT_NODES_SIZE)), m_Derivatives_Y(Matrix(1, ELEMENT_NODES_SIZE)) {}

void Derivatives::Calculate(const Jacobian& jacobian, int integrationPoint)
{
	IntegrationPointDerivatives* derivatives = IntegrationPointDerivatives::GetInstance();

	auto& derivativesETA = derivatives->GetETADerivatives(integrationPoint);
	auto& derivativesKSI = derivatives->GetKSIDerivatives(integrationPoint);

	for (int i = 0; i < 4; i++)
	{
		double dN_dx = jacobian.GetInversedMatrixAt(0, 0) * derivativesKSI.at(i) + jacobian.GetInversedMatrixAt(0, 1) * derivativesETA.at(i);
        m_Derivatives_X.SetElement(0, i, dN_dx);

		double dN_dy = jacobian.GetInversedMatrixAt(1, 0) * derivativesKSI.at(i) + jacobian.GetInversedMatrixAt(1, 1) * derivativesETA.at(i);
        m_Derivatives_Y.SetElement(0, i, dN_dy);
	}
}

std::ostream& operator<<(std::ostream& os, const Derivatives& derivatives)
{
    os << std::fixed << std::setprecision(PRINT_PRECISION);

    // Print X Derivatives

    os << "\n";

    for (int i = 0; i < 4; i++) 
        os  << "dN" << i + 1 << "/dx" << "\t";
    os << "\n";

    os << derivatives.m_Derivatives_X << "\n";

    // Print Y Derivatives

    for (int i = 0; i < 4; i++)
        os << "dN" << i + 1 << "/dy" << "\t";
    os << "\n";

    os << derivatives.m_Derivatives_Y;

    return os;
}
