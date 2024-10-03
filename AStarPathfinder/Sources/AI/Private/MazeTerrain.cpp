#include "MazeTerrain.h"

#include "Geometry/VertexArray2D.h"

#include <iostream>
#include <random>

std::default_random_engine rGen;
using intRand = std::uniform_int_distribution<int>;

namespace
{
	uint64_t NbrIteration = 0;
}

MazeTerrain::MazeTerrain() 
	: MazeSize(0)
{
	drawables.insert({"VertArray", VertexArray2D()});
}

MazeTerrain::~MazeTerrain()
{
}

void MazeTerrain::Update(float delta)
{
	if (!IsGenerationDone.load(std::memory_order_relaxed))
	{
		ConstructLabyrinthe();
	}
}

void MazeTerrain::SetMazeSize(const IVec2& size)
{
	// Size must me even
	ensure(size.x % 2 == 0);
	ensure(size.y % 2 == 0);

	// this need to not be even
	MazeSize = size + 1;
	Maze.reserve(MazeSize.x * MazeSize.y);
	GetVertexArray().Resize(MazeSize.x * MazeSize.y);
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
				Maze.emplace_back(Wall());
				std::get<Unit<Wall>>(Maze[it]).parent = this;
				std::get<Unit<Wall>>(Maze[it]).pos = pos;
				std::get<Unit<Wall>>(Maze[it]).SetValue(it);

				if ((x != 0 && x != MazeSize.x - 1) && (y != 0 && y != MazeSize.y - 1) && !(xTrue && yTrue))
				{
					WallList.push_back(pos);
					std::get<Unit<Wall>>(Maze[it]).bCanBeOpen = true;
				}

				GetVertexArray()[it].FillColor({ 255, 102, 153 });
			}
			else
			{
				Maze.emplace_back(Path());
				std::get<Unit<Path>>(Maze[it]).parent = this;
				std::get<Unit<Path>>(Maze[it]).pos = pos;
				std::get<Unit<Path>>(Maze[it]).SetValue(it);
				GetVertexArray()[it].FillColor({0,0,0});
			}
			GetVertexArray()[it].transform.scale = {4, 4};
			GetVertexArray()[it].transform.pos = pos * GetVertexArray()[it].transform.scale;
			++it;
		}
	}
}

void MazeTerrain::RegenerateLabyrinthe()
{
	ClearLabyrinthe();
	IsGenerationDone.exchange(false, std::memory_order_relaxed);
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
	RegenerateLabyrinthe();
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
	GetVertexArray().Resize(0);

	GenerateTerrain(MazeSize - 1);
}

void MazeTerrain::RemoveWall(Wall* target)
{
	auto it = std::find(WallList.begin(), WallList.end(), target->pos);
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

	Cell& cell = Maze[pos.x * MazeSize.x + pos.y];
	if (std::visit([pos](auto&& tmp)
		{
			return tmp.pos == pos;
		}, cell))
	{
		return &cell;
	}
	return nullptr;
}

VertexArray2D& MazeTerrain::GetVertexArray()
{
	return std::get<VertexArray2D>(drawables.at("VertArray"));
}

void MazeTerrain::AlgoLabyrinthe()
{
	size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
	IVec2 pos = WallList[index];

	Unit<Wall>* wallPath = std::get_if<Unit<Wall>>(GetCellByPos(pos));
	ensure(wallPath);
	uint64_t val = wallPath->value;

	GetVertexArray()[val].FillColor({ 0,0,0 });

	// Transform the wall to a path

	Cell* CurrentCellPtr = ChangeCellAt<Path>(pos);
	WallList.erase(WallList.begin() + index);

	if (Unit<Path>* currPath = std::get_if<Unit<Path>>(CurrentCellPtr))
	{
		ensure(currPath);
		currPath->parent = this;
		currPath->pos = pos;
		currPath->ChangeValue(val);
	}
	else
	{
		PLATEFORM_BREAK
	}

	if (WallList.size() <= 0)
	{
		IsGenerationDone.exchange(true, std::memory_order_relaxed);
	}
}
