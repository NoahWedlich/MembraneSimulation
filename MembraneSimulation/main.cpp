#include <iostream>
#include "Node.h"
#include "BoundaryNode.h"
#include "ConstraintManager.h"
#include "MCSolver.h"

int main()
{
	const int length_grid = 20;

	std::vector<Node> nodes{};
	std::vector<BoundaryNode> boundaries{};

	for (int y = -1; y <= length_grid; ++y)
	{
		for (int x = -1; x <= length_grid; ++x)
		{
			if (y == -1 || y == length_grid || x == -1 || x == length_grid)
			{
				boundaries.push_back(BoundaryNode(x, y, 0));
			}
			else
			{
				nodes.push_back(Node( x, y, 0 ));
			}
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
		for (BoundaryNode& other : boundaries)
		{
			double dist = node.distance(&other);
			if (dist > 0 && dist < 1.1)
			{
				node.add_boundary_neighbor(&other);
			}
		}
	}

	for (Node& node : nodes)
	{
		ConstraintManager::register_neighbor_interaction(&node, 100);
	}

	MCSolver::register_nodes(nodes);
	MCSolver::run_simulation(100000, 100, true);
}