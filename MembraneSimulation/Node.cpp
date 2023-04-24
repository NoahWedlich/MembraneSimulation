#include "Node.h"

Node::Node()
    : pos_(0, 0, 0), start_pos_(0, 0, 0), move_mask_(1, 1, 1), neighbors_(), boundaries_(), constraints_()
{}

Node::Node(Vec3 pos, Vec3 move_mask)
    : pos_(pos), start_pos_(pos), move_mask_(move_mask), neighbors_(), boundaries_(), constraints_()
{}

Node::Node(double x0, double x1, double x2, Vec3 move_mask)
    : pos_(x0, x1, x2), start_pos_(x0, x1, x2), move_mask_(move_mask), neighbors_(), boundaries_(), constraints_()
{}

const Vec3& Node::pos() const
{ return pos_; }

const Vec3& Node::start_pos() const
{ return start_pos_; }

void Node::set_move_mask(Vec3 mask)
{ move_mask_ = mask; }

void Node::set_move_mask(double x0, double x1, double x2)
{ move_mask_ = Vec3(x0, x1, x2); }

void Node::add_neighbor(Node* neighbor)
{ neighbors_.push_back(neighbor); }

Node* Node::get_neighbor(size_t index) const
{ return neighbors_[index]; }

void Node::remove_neighbor(Node* neighbor)
{
    for (auto i = neighbors_.begin(); i!=neighbors_.end(); ++i)
    {
        if (*i == neighbor)
        { neighbors_.erase(i); }
    }
}

void Node::remove_neighbor(size_t index)
{
    int j = 0;
    for (auto i = neighbors_.begin(); i != neighbors_.end(); ++i)
    {
        if (j++ == index)
        { neighbors_.erase(i); }
    }
}

void Node::add_boundary_neighbor(BoundaryNode* neighbor)
{
    Vec3 boundary = neighbor->pos();
    boundaries_.push_back(boundary);
}

const std::vector<Node*>& Node::neighbors() const
{ return neighbors_; }

const std::vector<Vec3>& Node::boundaries() const
{ return boundaries_; }

double Node::distance(const Node* other) const
{
    return (other->pos_ - pos_).length();
}

double Node::distance_squared(const Node* other) const
{
    return (other->pos_ - pos_).length_squared();
}

double Node::distance(const BoundaryNode* other) const
{
    return (other->pos() - pos_).length();
}

double Node::distance_squared(const BoundaryNode* other) const
{
    return (other->pos() - pos_).length_squared();
}

void Node::temp_move(Vec3 dV)
{
    dV *= move_mask_;
    last_good_pos_ = pos_;
    last_translation_ = dV;
    pos_ += dV;
}

void Node::reject_move()
{ pos_ = last_good_pos_; }

void Node::accept_move()
{
    last_good_pos_ = pos_;
    
    for (Vec3& boundary : boundaries_)
    {
        boundary += last_translation_;
    }
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{ return (os << "Node( Pos : " << node.pos_ << " )"); }