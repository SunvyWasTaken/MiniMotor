#include "AStarPathfinding.h"
#include "MazeTerrain.h"
#include <iostream>

namespace
{
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

namespace PathFinderAlgo
{
	AStarPathfinding::AStarPathfinding(MazeTerrain*	_parent)
		: Start(nullptr)
		, End(nullptr)
		, parent(_parent)
	{
	}

	void AStarPathfinding::SetStart(Unit<Path>* start)
	{
		Start = start;
	}

	void AStarPathfinding::SetEnd(Unit<Path>* end)
	{
		End = end;
	}

	void AStarPathfinding::operator()()
	{
		if (!Start || !End)
		{
			std::cout << "Start or End is nullptr" << std::endl;
			return;
		}

		OpenList.push_back(Start);

		while (!OpenList.empty())
		{
			Unit<Path>* current = OpenList[0];
			for (auto& cell : OpenList)
			{
				if (cell->gCost < current->gCost)
				{
					current = cell;
				}
			}

			OpenList.erase(std::remove(OpenList.begin(), OpenList.end(), current), OpenList.end());
			CloseList.push_back(current);

			if (current == End)
			{
				std::cout << "Path found" << std::endl;
				return;
			}

			for (auto& neighbour : current->GetNeighbours())
			{
				if (std::find(CloseList.begin(), CloseList.end(), neighbour) != CloseList.end() || !neighbour->bCanBeOpen)
				{
					continue;
				}

				uint64_t newCostToNeighbour = (neighbour->pos - current->pos).length() + current->gCost;
				if (newCostToNeighbour < neighbour->gCost || std::find(OpenList.begin(), OpenList.end(), neighbour) == OpenList.end())
				{
					neighbour->gCost = newCostToNeighbour;
					neighbour->hCost = (End->pos - neighbour->pos).length();
					neighbour->beforePath = current;

					if (std::find(OpenList.begin(), OpenList.end(), neighbour) == OpenList.end())
					{
						OpenList.push_back(neighbour);
					}
				}
			}
		}
		std::cout << "No path found" << std::endl;
		for (auto& ha: CloseList)
		{
			parent->GetVertexArray()[ha->pos.x * parent->MazeSize.x + ha->pos.y].FillColor({255, 0, 0});
		}
	}

};
