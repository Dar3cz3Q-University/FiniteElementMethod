#include "Node.h"

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	os << "[" << node.x << ", " << node.y << "]";
	return os;
}
