// Copyright Shimmer Studios : All rights reserved.
// Create with WillyBucket

#pragma once

#include "World.h"

class Cell;

class MazeTerrain : public World
{
public:
	MazeTerrain();

	virtual ~MazeTerrain();

	void SetMazeSize(const IVec2& size);

	void GenerateTerrain(const IVec2& size);

	void GenerateLabyrinthe();

	void ClearLabyrinthe();

	void RemoveWall(const IVec2& pos);

	Cell* GetCellByPos(const IVec2& pos);

	// Transform a wall to a path
	void ChangeCellAt(const IVec2& pos);

	void AlgoLabyrinthe();

public:

	IVec2 MazeSize;

	std::vector<Cell*> Maze;

private:

	std::atomic<bool> IsGenerationDone = true;

	std::vector<IVec2> WallList;

};
