#pragma once

#include <vector>


struct CA
{
	CA() = default;
	CA(int N);
	void Initialize(int N);
	void NextGeneration();
	
	std::vector<std::vector<bool>> grid;
	int generation = 0;
	int m_n;
};

