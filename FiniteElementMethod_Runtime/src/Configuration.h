#pragma once

#include "IntegrationShema.h"

// Set number of integration points
constexpr IntegrationSchema INTEGRATION_SCHEMA = IntegrationSchema::TWO_POINTS;

// Set number of threads. If none is set, number of available threads is used
#define THREADS_COUNT 4

// Log Level
#define LOG_LEVEL spdlog::level::trace // TODO: Make custom enum for log level


constexpr int INTEGRATION_POINTS_COUNT = 1 << ((int) INTEGRATION_SCHEMA + 1); // TODO: Move this line to a different file
