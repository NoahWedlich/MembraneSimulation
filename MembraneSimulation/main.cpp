#include <iostream>
#include "Node.h"

int main()
{
	const size_t length_grid = 10;

	std::vector<Node> nodes{};
	for (int y = 0; y < length_grid; ++y)
	{
		for (int x = 0; x < length_grid; ++x)
		{
			nodes.push_back(Node( x, y, 0 ));
		}
	}

	for (Node& node : nodes)
	{
		for (Node& other : nodes)
		{
			double dist = node.distance(&other);
			if (dist > 0 && dist < 1.1)
			{
				node.add_neighbor(&other);
			}
		}
	}

	int temp = 0;
}