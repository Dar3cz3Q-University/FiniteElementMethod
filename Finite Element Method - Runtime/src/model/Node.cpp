#include "pch.h"

#include "Node.h"

Node::Node(double x, double y)
	: x(x), y(y)
{
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	os << "[" << node.x << ", " << node.y << "]";
	return os;
}
