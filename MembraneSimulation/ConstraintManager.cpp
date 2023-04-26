#include "ConstraintManager.h"

void ConstraintManager::register_neighbor_interaction(Node* node, double coeff)
{
	node->constraints_.push_back(
		new NeighborInteraction(node, coeff)
	);
}

void ConstraintManager::register_curvature(Node* first, Node* center, Node* third, double coeff, double angle)
{
	first->constraints_.push_back(
		new CurvatureEdge(first, center, third, coeff, Vec3(0, 0, 1))
	);
	center->constraints_.push_back(
		new CurvatureCenter(center, first, third, coeff, Vec3(0, 0, 1))
	);
	first->constraints_.push_back(
		new CurvatureEdge(first, center, third, coeff, Vec3(0, 0, 1))
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