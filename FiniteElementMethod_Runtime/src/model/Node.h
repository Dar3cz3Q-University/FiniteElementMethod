#pragma once

struct Node 
{
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
};

std::ostream& operator<<(std::ostream& os, const Node& node);
