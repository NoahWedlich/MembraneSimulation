#include "MCSolver.h"

std::vector<Node>* MCSolver::nodes_{};
double MCSolver::max_step = 0.1;

void MCSolver::register_nodes(std::vector<Node>& nodes)
{
	MCSolver::nodes_ = &nodes;
}

void MCSolver::run_simulation(size_t simulation_steps, size_t report_freuquency)
{
	for (size_t step = 0; step < simulation_steps; ++step)
	{
		for (size_t t = 0; t < MCSolver::nodes_->size(); ++t) MCSolver::run_step(std::rand() % MCSolver::nodes_->size());
		if (step % report_freuquency == 0)
		{
			double sum = 0;
			for (Node& node : *MCSolver::nodes_)
			{
				sum += node.pos().x2();
			}
			sum /= MCSolver::nodes_->size();

			std::cout << "Average z is: " << sum << std::endl;
		}
	}
}

void MCSolver::run_step(size_t index)
{
	Node& node = (* MCSolver::nodes_)[index];
	double initial = ConstraintManager::calculate_constraints(&node);

	Vec3 dV = MCSolver::rand_vec(MCSolver::max_step);

	node.temp_move(dV);

	double changed = ConstraintManager::calculate_constraints(&node);

	double energy_diff = changed - initial;

	if (MCSolver::random() > std::exp(-energy_diff)) node.reject_move();
	else node.accept_move();
}

double MCSolver::random()
{
	return (double)std::rand() / (double)RAND_MAX;
}

Vec3 MCSolver::rand_vec(const double scale)
{
	return Vec3(
		(2 * MCSolver::random() - 1) * scale,
		(2 * MCSolver::random() - 1) * scale,
		(2 * MCSolver::random() - 1) * scale
	);
}
