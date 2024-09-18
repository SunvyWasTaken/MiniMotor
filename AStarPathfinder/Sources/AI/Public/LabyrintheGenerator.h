#pragma once

#include "Vec2.h"

#include <atomic>
#include <array>
#include <map>

class Cell;
class Wall;
class IWorld;

struct LabyrintheGenerator
{
	static void GenerateLabyrinthe(IWorld* World, std::atomic<bool>& IsGenerationDone);

	static bool Get2Neighboor(const Wall* CurrentWall, std::map<IVec2, Cell*> CellList, std::array<Cell*, 2>& CellNeighboor);

};
