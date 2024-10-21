#include "pch.h"

#include "Derivatives.h"

Derivatives::Derivatives()
{
    size_t numberOfIntegrationPoints = INTEGRATION_POINTS.size();

    m_Derivatives_ETA.reserve(numberOfIntegrationPoints);
    m_Derivatives_KSI.reserve(numberOfIntegrationPoints);

    for (size_t i = 0; i < numberOfIntegrationPoints; i++)
    {
        std::vector<double> tempX = {
            -0.25 * (1.0 - INTEGRATION_POINTS[i].eta),
            0.25 * (1.0 - INTEGRATION_POINTS[i].eta),
            0.25 * (1.0 + INTEGRATION_POINTS[i].eta),
            -0.25 * (1.0 + INTEGRATION_POINTS[i].eta)
        };

        std::vector<double> tempY = {
            -0.25 * (1.0 - INTEGRATION_POINTS[i].ksi),
            -0.25 * (1.0 + INTEGRATION_POINTS[i].ksi),
            0.25 * (1.0 + INTEGRATION_POINTS[i].ksi),
            0.25 * (1.0 - INTEGRATION_POINTS[i].ksi)
        };

        m_Derivatives_KSI.push_back(tempX);
        m_Derivatives_ETA.push_back(tempY);
    }
}
