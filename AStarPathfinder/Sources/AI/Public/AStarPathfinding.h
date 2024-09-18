#pragma once
#include "Vec2.h"
#include "Terrain.h"

struct PathFinderAlgo
{
	static void AStarPathfinding(IWorld* World, IVec2 Start, IVec2 End);
};