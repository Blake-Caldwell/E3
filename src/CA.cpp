#include "CA.hpp"

#include <functional> //bind
#include <random> 



CA::CA(int N)
{
	Initialize(N);
}

void CA::Initialize(int N)
{
	for (int i = 0; i < N; i++)
	{
		grid.push_back(std::vector<bool>(N));
	}

	auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());

	for (int outter = 0; outter < N; outter++)
	{
		for (int inner = 0; inner < N; inner++)
		{
			grid[outter][inner] = gen();
		}
	}
}

void CA::NextGeneration()
{

}
