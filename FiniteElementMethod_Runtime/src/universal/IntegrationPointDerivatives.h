#pragma once

#include "Node.h"
#include "Configuration.h"

#include <cmath>

class IntegrationPointDerivatives
{
    // Singleton Pattern
public:
    ~IntegrationPointDerivatives();
    IntegrationPointDerivatives(IntegrationPointDerivatives&) = delete;
    void operator=(const IntegrationPointDerivatives&) = delete;
    static IntegrationPointDerivatives* GetInstance();

private:
    IntegrationPointDerivatives();

private:
    static IntegrationPointDerivatives* m_Instance;

    // Logic of the class
public:
    const Node& GetIntegrationPoint(int index) const { return m_IntegrationPoints.at(index); }
    const Node& GetIntegrationWeight(int index) const { return m_IntegrationWeights.at(index); }
    const std::vector<Node>& GetIntegrationPoints() const { return m_IntegrationPoints; }
    const std::vector<Node>& GetIntegrationWeights() const { return m_IntegrationWeights; }
    const std::vector<double>& GetKSIDerivatives(int index) const { return m_Derivatives_KSI.at(index); }
    const std::vector<double>& GetETADerivatives(int index) const { return m_Derivatives_ETA.at(index); }

private:
    std::vector<Node> m_IntegrationPoints;
    std::vector<Node> m_IntegrationWeights;
    std::map<int, std::vector<double>> m_Derivatives_KSI;
    std::map<int, std::vector<double>> m_Derivatives_ETA;

private:
    void CalculateIntegrationPoints();

public:
    friend std::ostream& operator<<(std::ostream& os, const IntegrationPointDerivatives& derivatives);
};

std::ostream& operator<<(std::ostream& os, const IntegrationPointDerivatives& derivatives);

inline static const std::vector<std::vector<double>> LEGENDRE_POINTS = {
    { 0.0 },
    { -sqrt(1.0 / 3.0), sqrt(1.0 / 3.0) },
    { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) },
    {
        -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
        -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
        sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
        sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))
    },
    {
        -((1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0))),
        -((1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0))),
        0.0,
        ((1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0))),
        ((1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)))
    }
};

inline static const std::vector<std::vector<double>> LEGENDRE_WEIGHTS = {
    { 2.0 },
    { 1.0, 1.0 },
    { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 },
    {
        (18.0 - sqrt(30.0)) / 36.0,
        (18.0 + sqrt(30.0)) / 36.0,
        (18.0 + sqrt(30.0)) / 36.0,
        (18.0 - sqrt(30.0)) / 36.0
    },
    {
        ((322.0 - 13.0 * sqrt(70.0)) / 900.0),
        ((322.0 + 13.0 * sqrt(70.0)) / 900.0),
        (128.0 / 225.0),
        ((322.0 + 13.0 * sqrt(70.0)) / 900.0),
        ((322.0 - 13.0 * sqrt(70.0)) / 900.0)
    }
};
