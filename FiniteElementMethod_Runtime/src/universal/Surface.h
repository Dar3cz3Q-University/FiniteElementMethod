#pragma once

#include "IntegrationPointDerivatives.h"

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


};

