#pragma once
#include <vector>
#include "Node.h"
#include "BoundaryNode.h"
#include "ConstraintManager.h"

class NodeGrid
{
public:
	NodeGrid(int len_0 = 1, int len_1 = 1, int len_2 = 1);

	std::vector<Node>::iterator begin();
	std::vector<Node>::const_iterator begin() const;
	std::vector<Node>::iterator end();
	std::vector<Node>::const_iterator end() const;

	const size_t dim() const;

	const size_t len_0() const;
	const size_t len_1() const;
	const size_t len_2() const;

	const size_t size() const;

	Node& operator[](const size_t index);
private:
	size_t dimension_;

	size_t len_0_;
	size_t len_1_;
	size_t len_2_;

	std::vector<Node> nodes_;
};

