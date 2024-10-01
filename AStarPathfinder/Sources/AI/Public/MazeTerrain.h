
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

	void GenerateLabyrinthe();

	void RemoveWall(Wall* target);

	IVec2 MazeSize;

	std::vector<Cell> Maze;

	Cell* GetCellByPos(const IVec2& pos);

	template <typename Type>
	Cell* ChangeCellAt(const IVec2& pos)
	{
		if (std::visit([&](auto&& tmp)->bool{return tmp.pos == pos; }, Maze[pos.x * MazeSize.x + pos.y]))
		{
			Maze[pos.x * MazeSize.x + pos.y] = Type();
			return &Maze[pos.x * MazeSize.x + pos.y];
		}
		return nullptr;
	}

private:

	bool GetWallPos(const IVec2& pos, size_t& index);

	VertexArray2D& GetVertexArray();

	std::vector<IVec2> WallList;

};
