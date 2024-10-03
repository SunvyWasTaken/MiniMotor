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
		SetStart(std::get_if<Unit<Path>>(parent->GetCellByPos({ 1, 1 })));
		SetEnd(std::get_if<Unit<Path>>(parent->GetCellByPos({ parent->MazeSize.x - 2, parent->MazeSize.y - 2 })));
		OpenList.clear();
		CloseList.clear();

		if (!Start || !End)
		{
			std::cout << "Start or End is nullptr" << std::endl;
			return;
		}

		// A* algorithm
	}

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
