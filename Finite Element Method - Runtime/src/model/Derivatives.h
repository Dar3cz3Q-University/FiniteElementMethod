#pragma once

#include "Node.h"

inline const std::vector<Node> INTEGRATION_POINTS =
{
    Node(-1.0 / sqrt(3.0), -1.0 / sqrt(3.0)),
    Node(1.0 / sqrt(3.0), -1.0 / sqrt(3.0)),
    Node(1.0 / sqrt(3.0), 1.0 / sqrt(3.0)),
    Node(-1.0 / sqrt(3.0), 1.0 / sqrt(3.0))
};

class Derivatives
{
public:
    Derivatives();

public:
    const std::vector<double>& GetETADerivatives(int index) { return m_Derivatives_ETA.at(index); }
    const std::vector<double>& GetKSIDerivatives(int index) { return m_Derivatives_KSI.at(index); }

private:
    std::vector<std::vector<double>> m_Derivatives_ETA;
    std::vector<std::vector<double>> m_Derivatives_KSI;
};
