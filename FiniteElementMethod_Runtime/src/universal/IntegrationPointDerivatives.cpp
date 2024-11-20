#include "pch.h"

#include "IntegrationPointDerivatives.h"

IntegrationPointDerivatives* IntegrationPointDerivatives::m_Instance = nullptr;

IntegrationPointDerivatives::IntegrationPointDerivatives()
{
    CalculateIntegrationPoints();

    for (size_t i = 0; i < INTEGRATION_POINTS_COUNT; i++)
    {
        double ksi = m_IntegrationPoints.at(i).ksi;
        double eta = m_IntegrationPoints.at(i).eta;

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

        m_Derivatives_KSI.insert({ i + 1, dN_dKsi });
        m_Derivatives_ETA.insert({ i + 1, dN_dEta });
    }
}

IntegrationPointDerivatives::~IntegrationPointDerivatives()
{
    if (!m_Instance)
        delete m_Instance;
}

IntegrationPointDerivatives* IntegrationPointDerivatives::GetInstance()
{
    if (!m_Instance)
        m_Instance = new IntegrationPointDerivatives();

    return m_Instance;
}

void IntegrationPointDerivatives::CalculateIntegrationPoints()
{
    auto& legendrePoints = LEGENDRE_POINTS.at((int) INTEGRATION_SCHEMA);
    auto& legendreWeights = LEGENDRE_WEIGHTS.at((int) INTEGRATION_SCHEMA);

    m_IntegrationPoints.reserve((int) INTEGRATION_SCHEMA);
    m_IntegrationWeights.reserve((int) INTEGRATION_SCHEMA);

    for (auto& x : legendrePoints) for (auto& y : legendrePoints)
        m_IntegrationPoints.push_back(Node(x, y));

    for (auto& x : legendreWeights) for (auto& y : legendreWeights)
        m_IntegrationWeights.push_back(Node(x, y));
}

std::ostream& operator<<(std::ostream& os, const IntegrationPointDerivatives& derivatives)
{
    const int numberWidth = 12;
    const int headerWidth = 5;
    const int precision = 4;
    const char separator = ' ';

    // Print KSI Derivatives

    os << std::left << std::setw(headerWidth) << std::setfill(separator) << " ";

    for (int i = 0; i < 4; i++)
        os << std::left << std::setw(numberWidth) << std::setfill(separator) << ("dN" + std::to_string(i + 1) + "/dKsi");
    os << "\n";

    for (auto& derivatives : derivatives.m_Derivatives_KSI)
    {
        os << std::left << std::setw(headerWidth) << std::setfill(separator) << ("pc" + std::to_string(derivatives.first));
        for (auto& derivative : derivatives.second)
            os << std::left << std::setw(numberWidth) << std::setfill(separator) << std::setprecision(precision) << derivative;
        os << "\n";
    }

    os << "\n";

    // Print ETA Derivatives

    os << std::left << std::setw(headerWidth) << std::setfill(separator) << " ";

    for (int i = 0; i < 4; i++)
        os << std::left << std::setw(numberWidth) << std::setfill(separator) << ("dN" + std::to_string(i + 1) + "/dEta");
    os << "\n";

    for (auto& derivatives : derivatives.m_Derivatives_ETA)
    {
        os << std::left << std::setw(headerWidth) << std::setfill(separator) << ("pc" + std::to_string(derivatives.first));
        for (auto& derivative : derivatives.second)
            os << std::left << std::setw(numberWidth) << std::setfill(separator) << std::setprecision(precision) << derivative;
        os << "\n";
    }

    return os;
}
