

#include "MazeTerrain.h"

#include "Geometry/VertexArray2D.h"
#include "Cell.h"
#include "ECS/Components/RendableComponent.h"

#include <random>

std::default_random_engine rGen(42);
using intRand = std::uniform_int_distribution<int>;

namespace
{
	uint64_t NbrIteration = 0;
}

MazeTerrain::MazeTerrain()
	: MazeSize(0)
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
	for (Entity* it : Maze)
	{
		RemoveEntity(*it);
	}
	Maze.clear();
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
				Cell* entity = SpawnEntity<Cell>(TO_TEXT("Wall {}", it), it, Wall(), pos);
				entity->SetSize({25, 25});
				entity->AddWorldOffset(pos * entity->GetSize());
				Maze.push_back(entity);

				if ((x != 0 && x != MazeSize.x - 1) && (y != 0 && y != MazeSize.y - 1) && !(xTrue && yTrue))
				{
					WallList.push_back(pos);
					entity->SetCanBeOpen(true);
				}
			}
			else
			{
				Cell* entity = SpawnEntity<Cell>(TO_TEXT("Path {}", it), it, Path(), pos);
				entity->SetSize({ 25, 25 });
				entity->AddWorldOffset(pos * entity->GetSize());
				Maze.push_back(entity);		
			}
			++it;
		}
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
	WallList.clear();

	GenerateTerrain(MazeSize - 1);
}

void MazeTerrain::RemoveWall(const IVec2& pos)
{
	auto it = std::find(WallList.begin(), WallList.end(), pos);
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
	return Maze[pos.x * MazeSize.x + pos.y];
}

void MazeTerrain::ChangeCellAt(const IVec2& pos)
{
	Cell* entity = Maze[pos.x * MazeSize.x + pos.y];
	entity->ChangeState(Path());
}

void MazeTerrain::AlgoLabyrinthe()
{

	if (WallList.size() <= 0)
	{
		return;
	}

	//size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
	size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
	IVec2 pos = WallList[index];

	Cell* currCell = GetCellByPos(pos);
	uint64_t val = currCell->GetFirstValideValue();

	ChangeCellAt(pos);
	WallList.erase(WallList.begin() + index);

	if (!currCell->IsState<Path>())
	{
		// early return here cuz something went wrong
		return;
	}

	currCell->ChangeValue(val);

	if (WallList.size() <= 0)
	{
		IsGenerationDone.exchange(true, std::memory_order_relaxed);
	}
}
