#include <iostream>
#include "NodeGrid.h"
#include "ConstraintManager.h"
#include "MCSolver.h"

//TODO: 1d, kräfte

int main()
{
	const int length_grid = 20;

	NodeGrid nodes{ 10, 10 };

	MCSolver::register_node_grid(nodes);
	MCSolver::run_simulation(100000, 100, false);
}