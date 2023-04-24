#include "ConstraintManager.h"

void ConstraintManager::register_neighbor_interaction(Node* node, double coeff)
{
	node->constraints_.push_back(
		new NeighborInteraction(node, coeff)
	);
}

double ConstraintManager::calculate_constraints(Node* node)
{
	double total = 0;
	for (Constraint* constraint : node->constraints_)
	{
		total += (*constraint)();
	}
	return total;
}