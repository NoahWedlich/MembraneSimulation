#pragma once
#include <iostream>
#include <vector>
#include "Vec3.h"
#include "BoundaryNode.h"

class Constraint;
class ConstraintManager;

class Node
{
public:
	Node();
	Node(Vec3 pos, Vec3 move_mask = Vec3(1, 1, 1));
	Node(double x0, double x1, double x2, Vec3 move_mask = Vec3(1, 1, 1));

	const Vec3& pos() const;
	const Vec3& start_pos() const;

	void set_move_mask(Vec3 mask);
	void set_move_mask(double x0, double x1, double x2);

	void add_neighbor(Node* neighbor);
	Node* get_neighbor(size_t index) const;
	void remove_neighbor(Node* neighbor);
	void remove_neighbor(size_t index);

	void add_boundary_neighbor(BoundaryNode* neighbor);

	const std::vector<Node*>& neighbors() const;
	const std::vector<Vec3>& boundaries() const;
	const std::vector<Vec3>& orig_bound() const;
	
	double distance(const Node* other) const;
	double distance_squared(const Node* other) const;
	double distance(const BoundaryNode* other) const;
	double distance_squared(const BoundaryNode* other) const;

	void temp_move(Vec3 dV);
	void reject_move();
	void accept_move();

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
	friend ConstraintManager;
private:
	Vec3 pos_;
	Vec3 start_pos_;
	Vec3 last_good_pos_;

	Vec3 last_translation_;

	Vec3 move_mask_;

	std::vector<Constraint*> constraints_;

	std::vector<Node*> neighbors_;
	std::vector<Vec3> boundaries_;
};

