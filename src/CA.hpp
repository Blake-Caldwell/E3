#pragma once

#include <vector>
#include <array>


struct CA
{
	CA() = default;
	CA(int N);
	void Initialize(int N);
	void NextGeneration();

	std::array<std::vector<std::vector<bool>>, 2> grids;

	bool currentGridIndex = 0;
	int generation = 0;
	int m_n;
};

