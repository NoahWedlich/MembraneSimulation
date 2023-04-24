#pragma once
#include <unordered_map>
#include <vector>
#include "Vec3.h"
#include "Node.h"
#include "Constraints.h"

class ConstraintManager
{
public:
	static void register_neighbor_interaction(Node* node, double coeff);

	static double calculate_constraints(Node* node);
};

