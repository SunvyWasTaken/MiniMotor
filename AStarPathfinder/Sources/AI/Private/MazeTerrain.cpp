

#include "MazeTerrain.h"

#include "Geometry/VertexArray2D.h"
#include "Cell.h"
#include "ECS/Components/RendableComponent.h"

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
	for (auto& it : Maze)
	{
		RemoveEntity(it);
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
				Entity entity = SpawnEntity(TEXT("Wall {}", it));
				entity.AddWorldOffset(pos);
				entity.SetSize({25, 25});
				entity.AddComponent<RendableComponent>(Texture{TEXT("Ressources/Brick_Block.png"), TextureCoord{IVec2{0, 0}, IVec2{438, 0}, IVec2{438, 438}, IVec2{0, 438}}});
				entity.AddComponent<Cell>(Wall(pos, this));
				Maze.push_back(entity);
				Cell& curr = entity.GetComponent<Cell>();
				std::get<Unit<Wall>>(curr).parent = this;
				std::get<Unit<Wall>>(curr).SetValue(it);

				if ((x != 0 && x != MazeSize.x - 1) && (y != 0 && y != MazeSize.y - 1) && !(xTrue && yTrue))
				{
					WallList.push_back(pos);
					std::get<Unit<Wall>>(curr).bCanBeOpen = true;
				}
			}
			else
			{
				Entity entity = SpawnEntity(TEXT("Path {}", it));
				entity.AddWorldOffset(pos);
				entity.SetSize({ 25, 25 });
				entity.AddComponent<RendableComponent>(Texture{TEXT("Ressources/Brick_Block.png"), TextureCoord{ IVec2{438, 0}, IVec2{876, 0}, IVec2{876, 438}, IVec2{438, 0}}});
				entity.AddComponent<Cell>(Path(pos, this));
				Maze.push_back(entity);
				Cell& curr = entity.GetComponent<Cell>();
				std::get<Unit<Path>>(curr).parent = this;
				std::get<Unit<Path>>(curr).SetValue(it);
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

void MazeTerrain::RemoveWall(const Entity& target)
{
	auto it = std::find(WallList.begin(), WallList.end(), target.GetWorldPosition());
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
	return &Maze[pos.x * MazeSize.x + pos.y].GetComponent<Cell>();
}

Unit<Path>* MazeTerrain::ChangeCellAt(const IVec2& pos)
{
	Maze[pos.x * MazeSize.x + pos.y].GetComponent<Cell>() = Path(pos, this);
	return std::get_if<Unit<Path>>(&Maze[pos.x * MazeSize.x + pos.y].GetComponent<Cell>());

}

void MazeTerrain::AlgoLabyrinthe()
{
	size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
	IVec2 pos = WallList[index];

	Cell* wallPath = GetCellByPos(pos);
	ensure(wallPath);
	uint64_t val = std::get_if<Unit<Wall>>(wallPath)->value;

	// Transform the wall to a path
	if (Unit<Path>* currPath = ChangeCellAt(pos))
	{
		WallList.erase(WallList.begin() + index);
		ensure(currPath);
		currPath->parent = this;
		currPath->ChangeValue(val, Maze[pos.x * MazeSize.x + pos.y]);
	}

	if (WallList.size() <= 0)
	{
		IsGenerationDone.exchange(true, std::memory_order_relaxed);
	}
}
