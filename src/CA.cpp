#include "CA.hpp"

#include <functional> //bind
#include <random> 



CA::CA(int N)
{
	Initialize(N);
}

void CA::Initialize(int N)
{
	m_n = N;

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
	std::vector<std::vector<bool>> newGrid(m_n);

	for (int i = 0; i < m_n; i++)
	{
		for (int j = 0; j < m_n; j++)
		{
			newGrid[i].push_back(false);
		}
	}
		

	const int xNeighbours[] = {-1, 0, 1};
	const int yNeighbours[] = {-1, 0, 1};

	for (int outter = 0; outter < m_n; outter++)//target vector
	{
		for (int inner = 0; inner < m_n; inner++)//target cell
		{
			int neighbours;
			grid.at(outter).at(inner) == true ? neighbours = -1 : neighbours = 0; //if the current cell is 1 or 0

			for (int x = 0; x < 3; x++) //x neighbour
			{
				for (int y = 0; y < 3; y++) //y neighbour
				{
					try{
						if (grid.at(outter + xNeighbours[x]).at(inner + yNeighbours[y]))
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

			if (grid[outter][inner])
			{
				if (neighbours == 2 || neighbours == 3)
				{
					newGrid[outter][inner] = true;
				}
				else
				{ 
					newGrid[outter][inner] = false;
				}
			}
			else
			{
				if (neighbours == 3)
				{
					newGrid[outter][inner] = true;
				}
				else
				{
					newGrid[outter][inner] = false;
				}
			}
		}
	}

	grid = newGrid;
	generation++;

}
