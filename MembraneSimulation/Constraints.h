#pragma once
#include "Node.h"

class Constraint
{
public:
	virtual const double operator()() const = 0;
};

class NeighborInteraction : public Constraint
{
public:
	NeighborInteraction(Node* node, double coeff);

	virtual const double operator()() const override;
private:
	Node* node_;
	double coeff_;
};