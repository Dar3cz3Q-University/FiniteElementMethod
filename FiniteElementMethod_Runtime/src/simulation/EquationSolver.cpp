#include "pch.h"
#include "EquationSolver.h"

EquationSolver::EquationSolver(const GlobalData& data, const Matrix& H, const Matrix& C, const Matrix& P)
	: m_GlobalData(data), m_Matrix_C(C), m_Vector_P(P)
{
	m_dT_Coef = (1.0 / data.GetSimulationStepTime());

	m_Matrix_A = H + C * m_dT_Coef;

	int n = m_GlobalData.GetReadNodesNumber();
	int initialTemp = m_GlobalData.GetInitialTemp();

	m_Vector_T = Matrix(n, 1);

	for (int i = 0; i < n; i++) m_Vector_T.SetElement(i, 0, initialTemp);

	VTKFileWriter::GetInstance().SaveTemperatureInTime(m_Vector_T);
}

void EquationSolver::Run()
{
	auto [ L, U ] = NumericalMethods::LUDecomposition(m_Matrix_A);

	double dt = m_GlobalData.GetSimulationStepTime();

	for (double time = dt; time <= m_GlobalData.GetSimulationTime(); time += dt)
	{
		LOG_INFO("Simulation time = {}", time);

		Matrix b = (m_Matrix_C * m_dT_Coef) * m_Vector_T + m_Vector_P;
		Matrix y = NumericalMethods::ForwardSubstitution(L, b);
		Matrix x = NumericalMethods::BackwardSubstitution(U, y);

		m_Vector_T = x;

		VTKFileWriter::GetInstance().SaveTemperatureInTime(m_Vector_T);
	}
}
