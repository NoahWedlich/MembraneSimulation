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

	for (const Vec3& pos : node_->boundaries())
	{
		double r2 = (pos - node_->pos()).length_squared();
		if (r2 > 1)
		{ interaction += coeff_ * (r2 - 1) * (r2 - 1); }
		else
		{ interaction += 5 * coeff_ * (r2 - 1) * (r2 - 1); }
	}

	return interaction;
}

ExternalInteraction::ExternalInteraction(Node* node, Vec3& strength)
	: node_(node), strength_(strength)
{}

const double ExternalInteraction::operator()() const
{
	Vec3 interactions = -strength_ * node_->pos();
	return interactions.x0() + interactions.x1() + interactions.x2();
}