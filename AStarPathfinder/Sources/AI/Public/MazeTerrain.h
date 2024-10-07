
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

	virtual void Update(float delta) override;

	void SetMazeSize(const IVec2& size);

	void GenerateTerrain(const IVec2& size);

	void RegenerateLabyrinthe();

	void ConstructLabyrinthe();

	void GenerateLabyrinthe();

	void ClearLabyrinthe();

	void RemoveWall(Wall* target);

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

	void AlgoLabyrinthe();

public:

	IVec2 MazeSize;

	std::vector<Cell> Maze;

private:

	std::atomic<bool> IsGenerationDone = true;

	std::vector<IVec2> WallList;

};
