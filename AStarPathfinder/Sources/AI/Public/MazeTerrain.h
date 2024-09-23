
#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "Entitys.h"

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
		return nullptr;
	}

private:

	bool GetWallPos(const IVec2& pos, size_t& index);

	void GetAllNeighbors();

	VertexArray2D& GetVertexArray();

	std::vector<IVec2> WallList;

};
