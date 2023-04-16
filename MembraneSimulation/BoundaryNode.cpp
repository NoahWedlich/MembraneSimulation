#include "BoundaryNode.h"

BoundaryNode::BoundaryNode(Vec3 pos)
    : pos_(pos)
{}

BoundaryNode::BoundaryNode(double x0, double x1, double x2)
    : pos_(x0, x1, x2)
{}

const Vec3& BoundaryNode::pos() const
{  return pos_; }

std::ostream& operator<<(std::ostream& os, const BoundaryNode& node)
{ return (os << "BoundaryNode( Pos : " << node.pos_ << " )"); }
