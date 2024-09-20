#include "MazeTerrain.h"

#include "Debug/Debug.h"

#include "VertexArray2D.h"

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

	GetVertexArray().Resize((MazeSize.x) * (MazeSize.y));
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

				if ((!xTrue && !yTrue) || ((x > 0 && x < MazeSize.x - 1) && (y > 0 && y < MazeSize.y - 1)))
				{
					WallList.push_back(pos);
				}
				//else
				//{
				//	std::get<Unit<Wall>>(Maze.at(pos)).value = -1;
				//}
				GetVertexArray()[it].FillColor({ 255, 102, 153 });
			}
			else
			{
				Maze.emplace_back(Path());
				std::get<Unit<Path>>(Maze[it]).parent = this;
				std::get<Unit<Path>>(Maze[it]).SetValue(it);
				GetVertexArray()[it].FillColor({0,0,0});
			}
			GetVertexArray()[it].transform.scale = {5, 5};
			GetVertexArray()[it].transform.pos = pos * GetVertexArray()[it].transform.scale;
			++it;
		}
	}
}

void MazeTerrain::GenerateLabyrinthe(std::atomic<bool>& IsGenerationDone)
{
	
	GetAllNeighbors();
	uint64_t val = -1;
	while (!IsGenerationDone.load(std::memory_order_relaxed))
	{
		++val;
		size_t index = intRand(0, (int)WallList.size() - 1)(rGen);
		IVec2 pos = WallList[index];

		if (Unit<Wall>* wallPath = std::get_if<Unit<Wall>>(GetCellByPos(pos)))
		{
			ensure(wallPath);
			val = wallPath->value;
		}

		GetVertexArray()[val].FillColor({ 0,0,0 });

		// Transform the wall to a path

		*GetCellByPos(pos) = Path();

		if (Unit<Path>* currPath = std::get_if<Unit<Path>>(GetCellByPos(pos)))
		{
			ensure(currPath);
			currPath->parent = this;
			GetAllNeighbors();
			currPath->ChangeValue(val);
		}
		else
		{
			__nop(); __debugbreak();
		}
		WallList.erase(WallList.begin() + index);

		if (WallList.size() <= 0)
		{
			IsGenerationDone.exchange(true, std::memory_order_relaxed);
		}
	}
}

void MazeTerrain::RemoveWall(Wall* target)
{
	for(auto& cell : Maze)
	{
		if (Unit<Wall>* wall = std::get_if<Unit<Wall>>(&cell))
		{
			if (wall->value == target->value)
			{
				auto it = std::find(WallList.begin(), WallList.end(), wall->pos);
				if (it != WallList.end())
				{
					WallList.erase(it);
				}
				return;
			}
		}
	}
}

Cell* MazeTerrain::GetCellByPos(const IVec2& pos)
{
	for (auto& cell : Maze)
	{
		if (std::visit([pos](auto&& tmp)
			{
				return tmp.pos == pos;
			}, cell))
		{
			return &cell;
		}
	}
	return nullptr;
}

void MazeTerrain::GetAllNeighbors()
{
	for (auto& cell : Maze)
	{
		std::visit([](auto&& tmp)
			{
				tmp.GetNeighbor();
			}, cell);
	}
}

VertexArray2D& MazeTerrain::GetVertexArray()
{
	return std::get<VertexArray2D>(drawables.at("VertArray"));
}
