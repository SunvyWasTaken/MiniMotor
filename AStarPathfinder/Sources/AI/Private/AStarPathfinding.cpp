
#include "AStarPathfinding.h"
#include "MazeTerrain.h"

namespace PathFinderAlgo
{
	AStarPathfinding::AStarPathfinding(MazeTerrain*	_parent)
		: Start(nullptr)
		, End(nullptr)
		, parent(_parent)
	{
	}

	void AStarPathfinding::SetStart(Cell* start)
	{
		Start = start;
	}

	void AStarPathfinding::SetEnd(Cell* end)
	{
		End = end;
	}

	void AStarPathfinding::operator()()
	{
		SetStart(parent->GetCellByPos({ 1, 1 }));
		SetEnd(parent->GetCellByPos({ parent->MazeSize.x - 2, parent->MazeSize.y - 2 }));
		OpenList.clear();
		CloseList.clear();

		if (!Start || !End)
		{
			std::cout << "Start or End is nullptr" << std::endl;
			return;
		}

		OpenList.emplace_back(Start);

		while(!OpenList.empty())
		{

			Cell* UnitCell = OpenList[0];

			for (Cell* curr : OpenList)
			{
				if (curr->hCost < UnitCell->hCost) {
					UnitCell = curr;
				}
			}

			auto it = std::find(OpenList.begin(), OpenList.end(), UnitCell);
			if (it != OpenList.end())
			{
				OpenList.erase(it);
			}
			CloseList.emplace_back(UnitCell);	

			if (UnitCell == End)
			{
				std::cout << "End found" << std::endl;
				while (UnitCell != Start)
				{
					UnitCell = UnitCell->beforePath;
				}
				break;
			}
			NeighboursList NeighborList = UnitCell->GetNeighbours();

			for (auto Neighbor : NeighborList)
			{
				if (std::find(CloseList.begin(), CloseList.end(), Neighbor) == CloseList.end())
				{
					//Neighbor->gCost = UnitCell->gCost + (Neighbor->transform.pos - UnitCell->transform.pos).length();
					//Neighbor->hCost = (End->transform.pos - Neighbor->transform.pos).length();
					//Neighbor->beforePath = UnitCell;
					//OpenList.emplace_back(Neighbor);
				}
			}
		}
	}
};
