
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

	template <typename Type>
	Cell* ChangeCellAt(const IVec2& pos)
	{
		for (size_t i = 0; i < Maze.size(); ++i)
		{
			if (std::visit([&](auto&& tmp)->bool{return tmp.pos == pos;}, Maze[i]))
			{
				Maze[i] = Type();
				return &Maze[i];
			}
		}
	
	}

private:

	void GetAllNeighbors();

	VertexArray2D& GetVertexArray();

	std::vector<IVec2> WallList;

};
