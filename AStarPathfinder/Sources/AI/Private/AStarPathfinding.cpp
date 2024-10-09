
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

		OpenList.emplace_back(Start);

		while(!OpenList.empty())
		{

			Unit<Path>* UnitCell = OpenList[0];

			for (Unit<Path>* curr : OpenList)
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
			std::vector<Unit<Path>*> NeighborList = UnitCell->GetNeighbours();

			for (auto Neighbor : NeighborList)
			{

				if (std::find(CloseList.begin(), CloseList.end(), Neighbor) == CloseList.end())
				{
					Neighbor->gCost = UnitCell->gCost + (Neighbor->transform.pos - UnitCell->transform.pos).length();
					Neighbor->hCost = (End->transform.pos - Neighbor->transform.pos).length();
					Neighbor->beforePath = UnitCell;
					OpenList.emplace_back(Neighbor);
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
