#pragma once
#include <iostream>
#include "Vec3.h"

class BoundaryNode
{
public:
	BoundaryNode(Vec3 pos);
	BoundaryNode(double x0, double x1, double x2);

	const Vec3& pos() const;

	friend std::ostream& operator<<(std::ostream& os, const BoundaryNode& node);
private:
	Vec3 pos_;
};

