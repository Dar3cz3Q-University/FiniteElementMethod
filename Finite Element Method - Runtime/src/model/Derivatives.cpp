#include "pch.h"

#include "Derivatives.h"

Derivatives::Derivatives()
{
    m_Derivatives_ETA.reserve(INTEGRATION_POINTS_COUNT);
    m_Derivatives_KSI.reserve(INTEGRATION_POINTS_COUNT);

    for (size_t i = 0; i < INTEGRATION_POINTS_COUNT; i++)
    {
        double ksi = INTEGRATION_POINTS[i].ksi;
        double eta = INTEGRATION_POINTS[i].eta;

        std::vector<double> dN_dKsi = {
            -0.25 * (1.0 - eta),
            0.25 * (1.0 - eta),
            0.25 * (1.0 + eta),
            -0.25 * (1.0 + eta)
        };

        std::vector<double> dN_dEta = {
            -0.25 * (1.0 - ksi),
            -0.25 * (1.0 + ksi),
            0.25 * (1.0 + ksi),
            0.25 * (1.0 - ksi)
        };

        m_Derivatives_KSI.push_back(dN_dKsi);
        m_Derivatives_ETA.push_back(dN_dEta);
    }
}
