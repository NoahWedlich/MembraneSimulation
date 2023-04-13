#include "Constraints.h"

NeighborInteraction::NeighborInteraction(Node* node, double coeff)
	: node_(node), coeff_(coeff)
{}

const double NeighborInteraction::operator()() const
{
	double interaction = 0;
	for (Node* neighbor : node_->neighbors())
	{
		double r2 = node_->distance_squared(neighbor);
		if (r2 > 1)
		{ interaction += coeff_ * (r2 - 1) * (r2 - 1); }
		else
		{ interaction += 5 * coeff_ * (r2 - 1) * (r2 - 1); }
	}
	return interaction;
}