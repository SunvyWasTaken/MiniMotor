#include "MazeTerrain.h"

#include "Geometry/VertexArray2D.h"

#include <iostream>
#include <random>

std::default_random_engine rGen;
using intRand = std::uniform_int_distribution<int>;

MazeTerrain::MazeTerrain() 
	: MazeSize(0)
{
	drawables.insert({"VertArray", VertexArray2D()});
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
	Maze.reserve(MazeSize.x * MazeSize.y);
	GetVertexArray().Resize(MazeSize.x * MazeSize.y);
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
			GetVertexArray()[it].transform.scale = {2, 2};
			GetVertexArray()[it].transform.pos = pos * GetVertexArray()[it].transform.scale;
			++it;
		}
	}
}

void MazeTerrain::GenerateLabyrinthe()
{
	uint64_t val = -1;
	//uint8_t it = 0;
	std::atomic<bool> IsGenerationDone = false;
	while (/*it <= 5 && */!IsGenerationDone.load(std::memory_order_relaxed))
	{
		//++it;
		size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
		IVec2 pos = WallList[index];

		Unit<Wall>* wallPath = std::get_if<Unit<Wall>>(GetCellByPos(pos));
		ensure(wallPath);
		val = wallPath->value;

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
			std::cout << "Generation Done" << std::endl;
		}
	}
}

void MazeTerrain::RemoveWall(Wall* target)
{
	//size_t index = (WallList.size() - 1) * 0.5;

	//if (GetWallPos(target->pos, index))
	//{
	//	WallList.erase(WallList.begin() + index);
	//}

	auto it = std::find(WallList.begin(), WallList.end(), target->pos);
	if (it != WallList.end())
	{
		WallList.erase(it);
	}
	return;

}

//Cell* MazeTerrain::GetCellByPos(const IVec2& pos)
//{
//	for (auto& cell : Maze)
//	{
//		if (std::visit([pos](auto&& tmp)
//			{
//				return tmp.pos == pos;
//			}, cell))
//		{
//			return &cell;
//		}
//	}
//	return nullptr;
//}

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

bool MazeTerrain::GetWallPos(const IVec2& pos, size_t& index)
{
	if(index >= WallList.size() - 1 || (pos.x % 2 == 0 && pos.y % 2 == 0) || (pos.x >= MazeSize.x - 1 || pos.y >= MazeSize.y - 1) || (pos.x <= 0 || pos.y <= 0)) { return false; }

	if (WallList[index] < pos)
	{
		index *= 1.5;
	}
	else if (pos < WallList[index])
	{
		index *= 0.5;
	}
	else if (WallList[index] == pos)
	{
		return true;
	}
	else
	{
		return false;
	}
	return GetWallPos(pos, index);
}

VertexArray2D& MazeTerrain::GetVertexArray()
{
	return std::get<VertexArray2D>(drawables.at("VertArray"));
}
