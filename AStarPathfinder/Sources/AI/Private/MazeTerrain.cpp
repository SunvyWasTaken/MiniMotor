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

	MazeSize = size;

	// this need to not be even
	GetVertexArray().Resize((MazeSize.x + 1) * (MazeSize.y + 1));
}

void MazeTerrain::GenerateTerrain(const IVec2& size)
{
	SetMazeSize(size);

	size_t it = 0;
	for (int x = 0; x <= MazeSize.x; ++x)
	{
		for (int y = 0; y <= MazeSize.y; ++y)
		{
			IVec2 pos = { x, y };

			if (x % 2 == 0 || y % 2 == 0)
			{
				Maze.insert({ pos, Path() });
				std::get<Unit<Path>>(Maze.at(pos)).parent = this;
				std::get<Unit<Path>>(Maze.at(pos)).SetValue(it);
				GetVertexArray()[it].FillColor({ 255, 102, 153 });
			}
			else
			{
				Maze.insert({ pos, Wall() });
				std::get<Unit<Wall>>(Maze.at(pos)).parent = this;
				std::get<Unit<Wall>>(Maze.at(pos)).SetValue(it);
				GetVertexArray()[it].FillColor({ 0, 0, 0 });
			}
			GetVertexArray()[it].transform.pos = pos;
			++it;
		}
	}
}

void MazeTerrain::GenerateLabyrinthe(MazeTerrain* Terrain, std::atomic<bool>& IsGenerationDone)
{
	uint8_t it = 0;
	while (it >= 5 || WallList.size() > 0)
	{
		size_t index = intRand(0, WallList.size() - 1)(rGen);
		IVec2 pos = WallList[index];
		Maze.at(pos) = Path();
		// Todo : Redefine neighbors
		std::get<Unit<Path>>(Maze.at(pos)).ChangeValue(1);
		WallList.erase(WallList.begin() + index);
	}
}

void MazeTerrain::RemoveWall(Wall* target)
{
	for(auto& [pos, cell] : Maze)
	{
		if (Unit<Wall>* wall = std::get_if<Unit<Wall>>(&cell))
		{
			if (wall->value == target->value)
			{
				auto it = std::find(WallList.begin(), WallList.end(), pos);
				if (it != WallList.end())
				{
					WallList.erase(it);
				}
				return;
			}
		}
	}
}

VertexArray2D& MazeTerrain::GetVertexArray()
{
	return std::get<VertexArray2D>(drawables.at("VertArray"));
}
