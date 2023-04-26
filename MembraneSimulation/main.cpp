#include <iostream>
#include "NodeGrid.h"
#include "ConstraintManager.h"
#include "MCSolver.h"

//TODO: 1d, kr�fte

int main()
{
	const int length_grid = 30;

	NodeGrid nodes{ length_grid, length_grid };

	MCSolver::register_node_grid(nodes);
	MCSolver::run_simulation(100000, 100, true);
}