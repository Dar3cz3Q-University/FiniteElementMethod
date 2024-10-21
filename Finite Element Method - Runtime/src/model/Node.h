#pragma once

struct Node 
{
public:
	double x = 0.0;
	double y = 0.0;

	union
	{
		double ksi, eta;
	};
};

std::ostream& operator<<(std::ostream& os, const Node& node);
