#include "ConstraintManager.h"

std::unordered_map<Node*, std::vector<Constraint*>> ConstraintManager::constraints_{};

void ConstraintManager::register_node(Node* node)
{
	ConstraintManager::constraints_[node] = std::vector<Constraint*>{};
}

void ConstraintManager::register_neighbor_interaction(Node* node, double coeff)
{
	if (!ConstraintManager::registered(node)) ConstraintManager::register_node(node);
	ConstraintManager::constraints_[node].push_back(
		new NeighborInteraction( node, coeff )
	);
}

double ConstraintManager::calculate_constraints(Node* node)
{
	if (!ConstraintManager::registered(node)) ConstraintManager::register_node(node);

	double total = 0;
	for (Constraint* constraint : ConstraintManager::constraints_[node])
	{
		total += (*constraint)();
	}
	return total;
}

bool ConstraintManager::registered(Node* node)
{
	auto it = ConstraintManager::constraints_.find(node);
	return !(it == ConstraintManager::constraints_.end());
}