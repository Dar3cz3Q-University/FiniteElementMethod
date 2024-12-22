#include "pch.h"

#include "GridGenerator.h"

Grid GridGenerator::generate(double x0, double x, double y0, double y, int nodes_x, int nodes_y)
{
	if (x0 > x || y0 > y)
		throw std::invalid_argument("Given coordinates values are invalid");

	if (nodes_x <= 0 || nodes_y <= 0)
		throw std::invalid_argument("Number of nodes cannot be less than or equal to zero");

	LOG_TRACE("Generating simple grid");

	Grid tempGrid;

	double xStep = (x - x0) / (nodes_x - 1);
	double yStep = (y - y0) / (nodes_y - 1);

	LOG_TRACE("Generating nodes");

	int nodeCounter = 0;

	for (double a = x0; a <= x; a += xStep) for (double b = y0; b <= y; b += yStep)
		tempGrid.AddNode(++nodeCounter, Node(a, b));
	
	LOG_TRACE("Connecting nodes into elements");

	int elementCounter = 0;

	for (int i = 1; i <= (nodes_x - 1) * (nodes_y); i++)
	{
		if (i % nodes_y == 0) continue;

		Element tempElement;

		tempElement.AddNode(i);
		tempElement.AddNode(i + nodes_y);
		tempElement.AddNode(i + nodes_y + 1);
		tempElement.AddNode(i + 1);

		tempGrid.AddElement(++elementCounter, tempElement);
	}

	return tempGrid;
}
