#pragma once

#include "IntegrationShema.h"

// Set number of integration points
constexpr IntegrationSchema INTEGRATION_SCHEMA = IntegrationSchema::TWO_POINTS;

// Set number of threads. If none is set, number of available threads is used
#define THREADS_COUNT 4

// Add ENABLE_DEBUG_PRINT symbol to see all Jacobians, etc.
//#define ENABLE_DEBUG_PRINT

// Log Level
#define LOG_LEVEL spdlog::level::info // TODO: Make custom enum for log level

constexpr int PRINT_PRECISION = 3;


constexpr int INTEGRATION_POINTS_COUNT = 1 << ((int) INTEGRATION_SCHEMA + 1); // TODO: Move this line to a different file
