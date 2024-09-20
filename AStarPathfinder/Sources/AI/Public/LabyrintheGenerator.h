#pragma once

#include "Vec2.h"

#include <atomic>
#include <array>
#include <map>

class AStarTerrain;

struct LabyrintheGenerator
{
	static void GenerateLabyrinthe(AStarTerrain* World, std::atomic<bool>& IsGenerationDone);


};
