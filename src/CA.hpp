#pragma once

#include <vector>
#include <array>


struct CA
{
	CA() = default;
	CA(int N);
	void Initialize(int N);
	void NextGeneration();
	
	std::vector<std::vector<bool>> grid;
	std::vector<std::vector<bool>> backgrid;

	int generation = 0;
	int m_n;
};

