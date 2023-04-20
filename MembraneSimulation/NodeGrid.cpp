#include "NodeGrid.h"

NodeGrid::NodeGrid(size_t len_0, size_t len_1, size_t len_2)
    : len_0_(len_0), len_1_(len_1), len_2_(len_2), nodes_()
{
    dimension_ = len_2 == 1 ? (len_1 == 1) ? (len_0 == 1) ? 0 : 1 : 2 : 3;
    Vec3 move_mask = Vec3{1.0, 1.0, 1.0};
    if (dimension_ == 1) move_mask = Vec3{ 1.0, 1.0, 0.0 };

    for (int x0 = 0; x0 < len_0; x0++)
    {
        for (int x1 = 0; x1 < len_1; x1++)
        {
            for (int x2 = 0; x2 < len_2; x2++)
            {
                nodes_.push_back(Node(x0, x1, x2, move_mask));
            }
        }
    }

    for (Node& node : nodes_)
    {
        for (Node& other : nodes_)
        {
            double dist = node.distance(&other);
            if (dist > 0 && dist < 1.1)
            {
                node.add_neighbor(&other);
            }
        }
    }

    for (Node& node : nodes_)
    {
        ConstraintManager::register_neighbor_interaction(&node, 100);
    }
}

std::vector<Node>::iterator NodeGrid::begin()
{ return nodes_.begin(); }

std::vector<Node>::const_iterator NodeGrid::begin() const
{ return nodes_.begin(); }

std::vector<Node>::iterator NodeGrid::end()
{ return nodes_.end(); }

std::vector<Node>::const_iterator NodeGrid::end() const
{ return nodes_.end(); }

const size_t NodeGrid::dim() const
{ return dimension_; }

const size_t NodeGrid::len_0() const
{ return len_0_; }

const size_t NodeGrid::len_1() const
{ return len_1_; }

const size_t NodeGrid::len_2() const
{ return len_2_; }

const size_t NodeGrid::size() const
{ return len_0_ * len_1_ * len_2_; }

Node& NodeGrid::operator[](const size_t index)
{ return nodes_[index]; }