#pragma once

#include "Grid.h"

class GridGenerator
{
public:
	Grid generate(double x0, double x, double y0, double y, int nodes_x, int nodes_y);
};

