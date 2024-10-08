#include "MazeTerrain.h"

#include "Geometry/VertexArray2D.h"
#include "Cell.h"
#include "World.h"

#include <iostream>
#include <random>

std::default_random_engine rGen;
using intRand = std::uniform_int_distribution<int>;

namespace
{
	uint64_t NbrIteration = 0;
}

MazeTerrain::MazeTerrain(World* world)
	: MazeSize(0)
	, m_World(world)
{

}

MazeTerrain::~MazeTerrain()
{
}

void MazeTerrain::SetMazeSize(const IVec2& size)
{
	// Size must me even
	ensure(size.x % 2 == 0);
	ensure(size.y % 2 == 0);

	// this need to not be even
	MazeSize = size + 1;
	for (auto it : Maze)
	{
		m_World->RemoveEntity((Entity*)it);
	}
	Maze.reserve(MazeSize.x * MazeSize.y);
	
	NbrIteration = MazeSize.x;
}

void MazeTerrain::GenerateTerrain(const IVec2& size)
{
	SetMazeSize(size);

	size_t it = 0;
	for (int x = 0; x < MazeSize.x; ++x)
	{
		for (int y = 0; y < MazeSize.y; ++y)
		{
			IVec2 pos = { x, y };

			bool xTrue = x % 2 == 0;
			bool yTrue = y % 2 == 0;

			if (xTrue || yTrue)
			{
				Unit<Wall>* wall = m_World->SpawnEntity<Wall>(pos, m_World);
				Maze.emplace_back(wall);
				wall->parent = this;
				wall->SetValue(it);

				if ((x != 0 && x != MazeSize.x - 1) && (y != 0 && y != MazeSize.y - 1) && !(xTrue && yTrue))
				{
					WallList.push_back(pos);
					wall->bCanBeOpen = true;
				}

			}
			else
			{
				Unit<Path>* path = m_World->SpawnEntity<Path>(pos, m_World);
				Maze.emplace_back(path);
				path->parent = this;
				path->SetValue(it);
			}
			++it;
		}
	}
}

void MazeTerrain::ConstructLabyrinthe()
{
	uint64_t it = 0;
	while (!IsGenerationDone.load(std::memory_order_relaxed))
	{
		++it;
		if (it >= 1000)
		{
			return;
		}
		AlgoLabyrinthe();
	}
}

void MazeTerrain::GenerateLabyrinthe()
{
	ClearLabyrinthe();
	IsGenerationDone.exchange(false, std::memory_order_relaxed);
	while (!IsGenerationDone.load(std::memory_order_relaxed))
	{
		AlgoLabyrinthe();
	}
}

void MazeTerrain::ClearLabyrinthe()
{
	IsGenerationDone.exchange(true, std::memory_order_relaxed);
	Maze.clear();
	WallList.clear();

	GenerateTerrain(MazeSize - 1);
}

void MazeTerrain::RemoveWall(Wall* target)
{
	auto it = std::find(WallList.begin(), WallList.end(), target->transform.pos);
	if (it != WallList.end())
	{
		WallList.erase(it);
	}
	return;
}

Cell* MazeTerrain::GetCellByPos(const IVec2& pos)
{
	if (pos.x <= 0 || pos.y <= 0 || pos.x >= MazeSize.x || pos.y >= MazeSize.y)
	{
		return nullptr;
	}

	Cell& cell = *static_cast<Cell*>(Maze[pos.x * MazeSize.x + pos.y]);
	if (std::visit([pos](auto&& tmp)->bool
		{
			return tmp.transform.pos == pos;
		}, cell))
	{
		return &cell;
	}
	return nullptr;
}

Unit<Path>* MazeTerrain::ChangeCellAt(const IVec2& pos)
{
	if (std::visit([&](auto&& tmp)->bool {return tmp.transform.pos == pos; }, *(Cell*)Maze[pos.x * MazeSize.x + pos.y]))
	{
		m_World->RemoveEntity((Entity*)Maze[pos.x * MazeSize.x + pos.y]);
		Maze[pos.x * MazeSize.x + pos.y] = m_World->SpawnEntity<Path>(pos, m_World);
		return (Unit<Path>*)Maze[pos.x * MazeSize.x + pos.y];
	}
	return nullptr;
}

void MazeTerrain::AlgoLabyrinthe()
{
	size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
	IVec2 pos = WallList[index];

	Unit<Wall>* wallPath = std::get_if<Unit<Wall>>(GetCellByPos(pos));
	ensure(wallPath);
	uint64_t val = wallPath->value;

	// Transform the wall to a path
	if (Unit<Path>* currPath = ChangeCellAt(pos))
	{
		WallList.erase(WallList.begin() + index);
		ensure(currPath);
		currPath->parent = this;
		currPath->ChangeValue(val);
	}

	if (WallList.size() <= 0)
	{
		IsGenerationDone.exchange(true, std::memory_order_relaxed);
	}
}
