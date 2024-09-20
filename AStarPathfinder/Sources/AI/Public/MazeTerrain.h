
#pragma once

#include "Cell.h"
#include "Entitys.h"

#include <map>

class Wall;

class MazeTerrain : public Entity
{
public:
	MazeTerrain();
	virtual ~MazeTerrain();

	void SetMazeSize(const IVec2& size);

	void GenerateTerrain(const IVec2& size);

	void GenerateLabyrinthe(std::atomic<bool>& IsGenerationDone);

	void RemoveWall(Wall* target);

	IVec2 MazeSize;

	std::vector<Cell> Maze;

	Cell* GetCellByPos(const IVec2& pos);

private:

	void GetAllNeighbors();

	VertexArray2D& GetVertexArray();

	std::vector<IVec2> WallList;

};
