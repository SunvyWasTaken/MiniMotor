#pragma once

#include "CoreMinimal.h"
#include "Cell.h"

namespace PathFinderAlgo
{
	struct AStarPathfinding
	{
		AStarPathfinding(MazeTerrain* _parent);
		~AStarPathfinding() = default;

		void SetStart(Unit<Path>* start);
		void SetEnd(Unit<Path>* end);

		void operator()();
		
	private:
		std::vector<Unit<Path>*> OpenList;
		std::vector<Unit<Path>*> CloseList;

		Unit<Path>* Start;
		Unit<Path>* End;

		MazeTerrain* parent;
	};

	/************************************************************************/
	/* Dijkstra																*/
	/************************************************************************/

	struct DijkstraPathfinding
	{
		DijkstraPathfinding(MazeTerrain* _parent);
		~DijkstraPathfinding() = default;

		void SetStart(Unit<Path>* start);
		void SetEnd(Unit<Path>* end);

		void operator()();

	private:
		// Todo create a priority queue

		Unit<Path>* Start;
		Unit<Path>* End;

		MazeTerrain* parent;
	};
};