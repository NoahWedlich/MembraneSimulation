#include "ConstraintManager.h"

void ConstraintManager::register_neighbor_interaction(Node* node, double coeff)
{
	node->constraints_.push_back(
		new NeighborInteraction(node, coeff)
	);
}

void ConstraintManager::register_external_interaction(Node* node, Vec3 strength)
{
	node->constraints_.push_back(
		new ExternalInteraction(node, strength)
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