#include "AStarPathfinding.h"
#include "MazeTerrain.h"
#include <iostream>

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
		SetStart(std::get_if<Unit<Path>>(parent->GetCellByPos({ 1, 1 })));
		SetEnd(std::get_if<Unit<Path>>(parent->GetCellByPos({ parent->MazeSize.x - 2, parent->MazeSize.y - 2 })));
		OpenList.clear();
		CloseList.clear();

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
				if (cell->hCost < current->hCost)
				{
					current = cell;
				}
			}

			OpenList.erase(std::remove(OpenList.begin(), OpenList.end(), current), OpenList.end());
			CloseList.push_back(current);

			if (current == End)
			{
				for (auto& curr : CloseList)
				{
					parent->GetVertexArray()[curr->pos.x * parent->MazeSize.x + curr->pos.y].FillColor({ 255, 0, 0 });
				}
				while (current != Start)
				{
					parent->GetVertexArray()[current->pos.x * parent->MazeSize.x + current->pos.y].FillColor({0, 255, 0});
					current = current->beforePath;
				}
				return;
			}

			for (auto& neighbour : current->GetNeighbours())
			{
				if (std::find(CloseList.begin(), CloseList.end(), neighbour) != CloseList.end())
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
	}

	/************************************************************************/
	/* Dijkstra																*/
	/************************************************************************/

	DijkstraPathfinding::DijkstraPathfinding(MazeTerrain* _parent)
		: Start(nullptr)
		, End(nullptr)
		, parent(_parent)
	{
	}

	void DijkstraPathfinding::SetStart(Unit<Path>* start)
	{
		Start = start;
	}

	void DijkstraPathfinding::SetEnd(Unit<Path>* end)
	{
		End = end;
	}

	void DijkstraPathfinding::operator()()
	{
		// Dijkstra algorithm
		SetStart(std::get_if<Unit<Path>>(parent->GetCellByPos({ 1, 1 })));
		SetEnd(std::get_if<Unit<Path>>(parent->GetCellByPos({ parent->MazeSize.x - 2, parent->MazeSize.y - 2 })));



	}

};
