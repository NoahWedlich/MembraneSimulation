#pragma once
#include <unordered_map>
#include <vector>
#include "Node.h"
#include "Constraints.h"

class ConstraintManager
{
public:
	static void register_node(Node* node);
	static void register_neighbor_interaction(Node* node, double coeff);

	static double calculate_constraints(Node* node);

	static bool registered(Node* node);
private:
	static std::unordered_map<Node*, std::vector<Constraint*>> constraints_;
};

