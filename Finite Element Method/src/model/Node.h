#pragma once

#include <iostream>

struct Node 
{
public:
	double x = 0.0;
	double y = 0.0;
};

std::ostream& operator<<(std::ostream& os, const Node& node);
