
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

	void GenerateLabyrinthe(MazeTerrain* Terrain, std::atomic<bool>& IsGenerationDone);

	void RemoveWall(Wall* target);

private:

	VertexArray2D& GetVertexArray();

	IVec2 MazeSize;

	std::map<IVec2, Cell> Maze;

	std::vector<IVec2> WallList;

};
