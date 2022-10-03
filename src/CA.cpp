#include "CA.hpp"

#include <functional> //bind
#include <random>
#include <thread>
#include <functional>



CA::CA(int N)
{
	Initialize(N);
	
};


void CA::Initialize(int N)
{
	m_n = N;

	for (int i = 0; i < N; i++)
	{
		grids[0].push_back(std::vector<bool>(N));
		grids[1].push_back(std::vector<bool>(N));
	}

	auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());

	for (int outter = 0; outter < N; outter++)
	{
		for (int inner = 0; inner < N; inner++)
		{
			grids[0][outter][inner] = gen();
		}
	}
}

const int xNeighbours[] = { -1, 0, 1 };
const int yNeighbours[] = { -1, 0, 1 };

void CA::NextGeneration()
{
	std::vector<std::vector<bool>>& backGrid = grids[currentGridIndex];
	std::vector<std::vector<bool>>& currentGrid = grids[(currentGridIndex = !currentGridIndex)];
	
	std::vector<std::thread> threads;
	for (int outter = 0; outter < m_n; outter++)//target vector
	{
		for (int inner = 0; inner < m_n; inner++)//target cell
		{
			int neighbours = 0;
			backGrid.at(outter).at(inner) == true ? neighbours = -1 : neighbours = 0; //if the current cell is 1 or 0

			for (int x = 0; x < 3; x++) //x neighbour
			{
				for (int y = 0; y < 3; y++) //y neighbour
				{

					try {
						if (backGrid.at(outter + xNeighbours[x]).at(inner + yNeighbours[y]))
						{
							neighbours++;
						}
					}
					catch (std::exception e)
					{
						//do nothing
					}
				}
			}

			if (backGrid[outter][inner])
			{
				if (neighbours == 2 || neighbours == 3)
				{
					currentGrid[outter][inner] = true;
				}
				else
				{
					currentGrid[outter][inner] = false;
				}
			}
			else
			{
				if (neighbours == 3)
				{
					currentGrid[outter][inner] = true;
				}
				else
				{
					currentGrid[outter][inner] = false;
				}
			}

		}
	}


	generation++;

}
