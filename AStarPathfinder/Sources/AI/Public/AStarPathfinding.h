#pragma once

#include "CoreMinimal.h"
#include "Cell.h"

namespace PathFinderAlgo
{
	struct AStarPathfinding
	{
		AStarPathfinding(MazeTerrain* _parent);
		~AStarPathfinding() = default;

		void SetStart(Cell* start);
		void SetEnd(Cell* end);

		void operator()();
		
	private:
		std::vector<Cell*> OpenList;
		std::vector<Cell*> CloseList;

		Cell* Start;
		Cell* End;

		MazeTerrain* parent;
	};
};