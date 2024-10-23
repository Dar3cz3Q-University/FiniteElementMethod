#pragma once

struct Node 
{
public:
	Node(double x, double y);

public:
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
