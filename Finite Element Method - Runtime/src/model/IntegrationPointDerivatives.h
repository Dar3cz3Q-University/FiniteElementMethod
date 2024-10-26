#pragma once

#include "Node.h"

#define THREE_INTEGRATION_POINTS

#ifdef THREE_INTEGRATION_POINTS

inline constexpr auto INTEGRATION_POINTS_COUNT = 9;

inline const std::vector<Node> INTEGRATION_POINTS =
{
    Node(0.0, 0.0),
    Node(0.0, sqrt(3.0 / 5.0)),
    Node(0.0, -sqrt(3.0 / 5.0)),
    Node(sqrt(3.0 / 5.0), 0.0),
    Node(sqrt(3.0 / 5.0), sqrt(3.0 / 5.0)),
    Node(sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0)),
    Node(-sqrt(3.0 / 5.0), 0.0),
    Node(-sqrt(3.0 / 5.0), sqrt(3.0 / 5.0)),
    Node(-sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0))
};

inline const std::vector<Node> INTEGRATION_WEIGHTS = 
{ 
    Node(8.0 / 9.0, 8.0 / 9.0),
    Node(8.0 / 9.0, 5.0 / 9.0),
    Node(8.0 / 9.0, 5.0 / 9.0),
    Node(5.0 / 9.0, 8.0 / 9.0),
    Node(5.0 / 9.0, 5.0 / 9.0),
    Node(5.0 / 9.0, 5.0 / 9.0),
    Node(5.0 / 9.0, 8.0 / 9.0),
    Node(5.0 / 9.0, 5.0 / 9.0),
    Node(5.0 / 9.0, 5.0 / 9.0)
};

#else

inline constexpr auto INTEGRATION_POINTS_COUNT = 4;

inline const std::vector<Node> INTEGRATION_POINTS =
{
    Node(-1.0 / sqrt(3.0), -1.0 / sqrt(3.0)),
    Node(1.0 / sqrt(3.0), -1.0 / sqrt(3.0)),
    Node(-1.0 / sqrt(3.0), 1.0 / sqrt(3.0)),
    Node(1.0 / sqrt(3.0), 1.0 / sqrt(3.0))
};

inline const std::vector<Node> INTEGRATION_WEIGHTS =
{
    Node(1.0, 1.0),
    Node(1.0, 1.0),
    Node(1.0, 1.0),
    Node(1.0, 1.0)
};

#endif

class IntegrationPointDerivatives
{
    // Singleton Pattern
private:
    IntegrationPointDerivatives();
    ~IntegrationPointDerivatives();

private:
    static IntegrationPointDerivatives* m_Instance;

public:
    IntegrationPointDerivatives(IntegrationPointDerivatives&) = delete;
    void operator=(const IntegrationPointDerivatives&) = delete;
    static IntegrationPointDerivatives* GetInstance();

    // Logic of the class
public:
    const std::vector<double>& GetKSIDerivatives(int index) const { return m_Derivatives_KSI.at(index); }
    const std::vector<double>& GetETADerivatives(int index) const { return m_Derivatives_ETA.at(index); }

private:
    std::unordered_map<int, std::vector<double>> m_Derivatives_KSI;
    std::unordered_map<int, std::vector<double>> m_Derivatives_ETA;

public:
    friend std::ostream& operator<<(std::ostream& os, const IntegrationPointDerivatives& derivatives);
};

std::ostream& operator<<(std::ostream& os, const IntegrationPointDerivatives& derivatives);
