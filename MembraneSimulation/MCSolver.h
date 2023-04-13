#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include "Vec3.h"
#include "Node.h"
#include "ConstraintManager.h"

class MCSolver
{
public:
	static void register_nodes(std::vector<Node>& nodes);

	static void run_simulation(size_t simulation_steps, size_t report_freuquency);
	static void run_step(size_t index);

	static double random();
	static Vec3 rand_vec(const double scale);

	static double max_step;
private:
	static std::vector<Node>* nodes_;
};

