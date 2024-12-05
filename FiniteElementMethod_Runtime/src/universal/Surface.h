#pragma once

#include "IntegrationPointDerivatives.h"
#include "SurfaceEnum.h"
#include "Matrix.h"

class Surface
{
    // Singleton Pattern
public:
    ~Surface();
    Surface(Surface&) = delete;
    void operator=(const Surface&) = delete;
    static Surface* GetInstance();

private:
    Surface();

private:
    static Surface* m_Instance;

    // Logic of the class
public:
    inline Matrix GetSurfaceMatrixForDirection(SurfaceEnum direction) const { return m_SurfaceMatricies.at(direction); }
    inline Matrix GetSurfaceVectorForDirection(SurfaceEnum direction) const { return m_PVectors.at(direction); }

private:
    std::map<SurfaceEnum, Matrix> m_SurfaceMatricies;
    std::map<SurfaceEnum, Matrix> m_PVectors;
};

inline static const std::map<int, std::function<double(double, double)>> SHAPE_FUNCTIONS = {
    { 1, [](double ksi, double eta) { return 0.25 * (1.0 - ksi) * (1.0 - eta); }},
    { 2, [](double ksi, double eta) { return 0.25 * (1.0 + ksi) * (1.0 - eta); }},
    { 3, [](double ksi, double eta) { return 0.25 * (1.0 + ksi) * (1.0 + eta); }},
    { 4, [](double ksi, double eta) { return 0.25 * (1.0 - ksi) * (1.0 + eta); }}
};

