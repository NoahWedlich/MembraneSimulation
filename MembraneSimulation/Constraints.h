#pragma once
#include "Vec3.h"
#include "Node.h"

class Constraint
{
public:
	virtual const double operator()() = 0;
};

class NeighborInteraction : public Constraint
{
public:
	NeighborInteraction(Node* node, double coeff);

	virtual const double operator()() override;
private:
	Node* node_;
	double coeff_;
};

class CurvatureCenter : public Constraint
{
public:
	CurvatureCenter(Node* center, Node* before, Node* after, double coeff, Vec3 dir);

	virtual const double operator()() override;
private:
	Node* this_;
	Node* before_;
	Node* after_;
	double coeff_;
	Vec3 curve_dir_;
};

class CurvatureEdge : public Constraint
{
public:
	CurvatureEdge(Node* this_node, Node* center, Node* other, double coeff, Vec3 dir);

	virtual const double operator()() override;
private:
	Node* this_;
	Node* center_;
	Node* other_;
	double coeff_;
	Vec3 curve_dir_;
};