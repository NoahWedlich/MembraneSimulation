#include "Constraints.h"

NeighborInteraction::NeighborInteraction(Node* node, double coeff)
	: node_(node), coeff_(coeff)
{}

const double NeighborInteraction::operator()()
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
		{ interaction += coeff_ * 5000 * (r2 - 1) * (r2 - 1); }
		else
		{ interaction += 10 * coeff_ * 5000 * (r2 - 1) * (r2 - 1); }
	}

	return interaction;
}

CurvatureCenter::CurvatureCenter(Node* center, Node* before, Node* after, double coeff, Vec3 dir)
	: this_(center), before_(before), after_(after), coeff_(coeff), curve_dir_(dir)
{}

const double CurvatureCenter::operator()()
{
	Vec3 dir = curve_dir_;

	Vec3 a = before_->pos() - this_->pos();
	Vec3 b = after_->pos() - this_->pos();
	Vec3 c = a + b;
	if (false && c.length_squared() > 0.001)
	{
		c /= c.length();
		Vec3 d = -c;
		Vec3 c_dir = curve_dir_ - c;
		Vec3 d_dir = curve_dir_ - d;
		double len_c = c_dir.length_squared();
		double len_d = d_dir.length_squared();
		if (len_c > 0.75 && len_c <= len_d)
		{ dir = c; }
		else if (len_d > 0.75)
		{ dir = d; }
	}

	double angle_b = a.angle(dir);
	double angle_a = b.angle(dir);
	double angle = angle_b + angle_a;

	double interaction = coeff_ * (angle - 0.9) * (angle - 0.9);
	return interaction;
}

CurvatureEdge::CurvatureEdge(Node* this_node, Node* center, Node* other, double coeff, Vec3 dir)
	: this_(this_node), center_(center), other_(other), coeff_(coeff), curve_dir_(dir)
{}

const double CurvatureEdge::operator()()
{
	Vec3 dir = curve_dir_;

	Vec3 a = this_->pos() - center_->pos();
	Vec3 b = other_->pos() - center_->pos();
	Vec3 c = a + b;
	if (false && c.length_squared() > 0.001)
	{
		c /= c.length();
		Vec3 d = -c;
		Vec3 c_dir = curve_dir_ - c;
		Vec3 d_dir = curve_dir_ - d;
		double len_c = c_dir.length_squared();
		double len_d = d_dir.length_squared();
		if (len_c > 0.75 && len_c <= len_d)
		{ dir = c; }
		else if (len_d > 0.75)
		{ dir = d; }
	}

	double angle_b = a.angle(dir);
	double angle_a = b.angle(dir);
	double angle = angle_b + angle_a;

	double interaction = coeff_ * (angle - 0.9) * (angle - 0.9);
	return interaction;
}