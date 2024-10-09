
#pragma once

#include "CoreMinimal.h"

class Wall;
class World;

template <typename Derived>
class Unit;

class Path;

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class MazeTerrain
{
public:
	MazeTerrain(World* world);

	virtual ~MazeTerrain();

	void SetMazeSize(const IVec2& size);

	void GenerateTerrain(const IVec2& size);

	void ConstructLabyrinthe();

	void GenerateLabyrinthe();

	void ClearLabyrinthe();

	void RemoveWall(Wall* target);

	Cell* GetCellByPos(const IVec2& pos);

	Unit<Path>* ChangeCellAt(const IVec2& pos);

private:

	void AlgoLabyrinthe();

public:

	IVec2 MazeSize;

	std::vector<Cell> Maze;

private:

	std::atomic<bool> IsGenerationDone = true;

	std::vector<IVec2> WallList;

	World* m_World;

};
