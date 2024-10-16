// Copyright Shimmer Studios : All rights reserved.
// Create with WillyBucket

#pragma once

#include "World.h"
#include "ECS/Entitys.h"

class Wall;

template <typename Derived>
class Unit;

class Path;

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class MazeTerrain : public World
{
public:
	MazeTerrain();

	virtual ~MazeTerrain();

	void SetMazeSize(const IVec2& size);

	void GenerateTerrain(const IVec2& size);

	void GenerateLabyrinthe();

	void ClearLabyrinthe();

	void RemoveWall(const Entity& target);

	Cell* GetCellByPos(const IVec2& pos);

	Unit<Path>* ChangeCellAt(const IVec2& pos);

private:

	void AlgoLabyrinthe();

public:

	IVec2 MazeSize;

	std::vector<Entity> Maze;

private:

	std::atomic<bool> IsGenerationDone = true;

	std::vector<IVec2> WallList;

};
