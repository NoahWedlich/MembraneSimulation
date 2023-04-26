#include "NodeGrid.h"

NodeGrid::NodeGrid(int len_0, int len_1, int len_2)
    : len_0_(len_0), len_1_(len_1), len_2_(len_2), nodes_()
{
    dimension_ = len_2 == 1 ? (len_1 == 1) ? (len_0 == 1) ? 0 : 1 : 2 : 3;
    Vec3 move_mask = Vec3{1.0, 1.0, 1.0};
    if (dimension_ == 1) move_mask = Vec3{ 1.0, 1.0, 0.0 };

    std::vector<BoundaryNode> boundaries{};

    for (int x0 = -1; x0 <= len_0; x0++)
    {
        for (int x1 = 0; x1 < len_1; x1++)
        {
            for (int x2 = 0; x2 < len_2; x2++)
            {
                if (x0 == -1 || x1 == -1 || x2 == -1 || x0 == len_0 || x1 == len_1 || x2 == len_2)
                {
                    boundaries.push_back(BoundaryNode(x0, x1, x2));
                }
                else
                {
                    nodes_.push_back(Node(x0, x1, x2, move_mask));
                }
            }
        }
    }

    //Fix one node, to stop the grid from drifting
    // nodes_[0].set_move_mask(Vec3{ 0.0, 0.0, 0.0 });

    int x0 = 11;
    for (int x1 = 9; x1 < 20; x1++)
    {
        int index = x0 + x1 * len_0;
        ConstraintManager::register_curvature(&nodes_[index], &nodes_[index + 1], &nodes_[index + 2], 200, 1);
        //ConstraintManager::register_curvature(&nodes_[index + 1], &nodes_[index + 2], &nodes_[index + 3], 100, 1);
        ConstraintManager::register_curvature(&nodes_[index + 2], &nodes_[index + 3], &nodes_[index + 4], 200, 1);
        //ConstraintManager::register_curvature(&nodes_[index + 3], &nodes_[index + 4], &nodes_[index + 5], 100, 1);
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

        for (BoundaryNode& other : boundaries)
        {
            double dist = node.distance(&other);
            if (dist > 0 && dist < 1.1)
            {
                node.add_boundary_neighbor(&other);
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
