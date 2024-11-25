#pragma once

struct Node 
{
	Node() = default;
	Node(double x, double y);

	union
	{
		struct
		{
			double x, y;
		};
		struct
		{
			double ksi, eta;
		};
	};

	bool IsBoundaryCondition = false;
};

std::ostream& operator<<(std::ostream& os, const Node& node);
