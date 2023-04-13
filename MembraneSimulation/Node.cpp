#include "Node.h"

Node::Node()
    : pos_(0, 0, 0), start_pos_(0, 0, 0), neighbors_(), constraints_()
{}

Node::Node(Vec3 pos)
    : pos_(pos), start_pos_(pos), neighbors_(), constraints_()
{}

Node::Node(double x0, double x1, double x2)
    : pos_(x0, x1, x2), start_pos_(x0, x1, x2), neighbors_(), constraints_()
{}

const Vec3& Node::pos() const
{ return pos_; }

const Vec3& Node::start_pos() const
{ return start_pos_; }

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

const std::vector<Node*>& Node::neighbors() const
{ return neighbors_; }

double Node::distance(const Node* other) const
{
    return (other->pos_ - pos_).length();
}

double Node::distance_squared(const Node* other) const
{
    return (other->pos_ - pos_).length_squared();
}

void Node::temp_move(Vec3 dV)
{
    last_good_pos_ = pos_;
    pos_ += dV;
}

void Node::reject_move()
{ pos_ = last_good_pos_; }

void Node::accept_move()
{ last_good_pos_ = pos_; }

std::ostream& operator<<(std::ostream& os, const Node& node)
{ return (os << "Node( Pos : " << node.pos_ << " )"); }