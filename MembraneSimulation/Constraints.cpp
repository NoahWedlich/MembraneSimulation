#include "Constraints.h"

NeighborInteraction::NeighborInteraction(Node* node, double coeff)
	: node_(node), coeff_(coeff)
{}

const double NeighborInteraction::operator()() const
{
	double interaction = 0;
	for (Node* neighbor : node_->neighbors())
	{
		double r2 = std::pow(node_->distance(neighbor), 2);
		if (r2 > 1)
		{ interaction += coeff_ * std::pow(r2 - 1, 2); }
		else
		{ interaction += 5 * coeff_ * std::pow(r2 - 1, 2); }
	}
	return interaction;
}