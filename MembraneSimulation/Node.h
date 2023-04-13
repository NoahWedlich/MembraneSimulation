#pragma once
#include <iostream>
#include <vector>
#include "Vec3.h"

class Node
{
public:
	Node();
	Node(Vec3 pos);
	Node(double x0, double x1, double x2);

	void add_neighbor(Node* neighbor);
	Node* get_neighbor(size_t index) const;
	void remove_neighbor(Node* neighbor);
	void remove_neighbor(size_t index);

	const std::vector<Node*> neighbors() const;
	
	double distance(const Node* other) const;

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
private:
	Vec3 pos_;
	Vec3 start_pos_;

	std::vector<Node*> neighbors_;
};

