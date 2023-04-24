#pragma once
#include "Vec3.h"
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

class ExternalInteraction : public Constraint
{
public:
	ExternalInteraction(Node* node, Vec3& strength);

	virtual const double operator()() const override;
private:
	Node* node_;
	Vec3 strength_;
};