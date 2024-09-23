
#include "Cell.h"

#include "MazeTerrain.h"

#include "Debug/Debug.h"


Wall::Wall()
	: Unit<Wall>()
	, neighbors()
{
}

void Wall::ChangeValue(uint64_t val)
{
	if(!bCanBeOpen)
		return;

	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(pos + side))
		{
			if (Unit<Path>* path = std::get_if<Unit<Path>>(curr))
			{
				if (path->value != val)
					return;
			}
		}

	}
	parent->RemoveWall(this);
	bCanBeOpen = false;
}

void Wall::GetNeighbor()
{
	if (!parent)
		return;

	(!neighbors.empty() || [&](){ neighbors.clear(); return false; }());

	std::array<IVec2, 4> Sides = { IVec2{1, 0}, IVec2{0, 1}, IVec2{-1, 0}, IVec2{0, -1} };
	for (auto& side : Sides)
	{
		IVec2 newPos = pos + side;
		if (newPos.x < 0 || newPos.y < 0 || newPos.x >= parent->MazeSize.x || newPos.y >= parent->MazeSize.y)
		{
			continue;
		}
		else if (Unit<Path>* curr = std::get_if<Unit<Path>>(parent->GetCellByPos(newPos)))
		{
			neighbors.emplace_back(curr);
		}
	}
}

Path::Path()
	: Unit<Path>()
	, neighbors()
{
}

void Path::ChangeValue(uint64_t val)
{
	if (value == val)
		return;

	value = val;
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(pos + side))
		{
			std::visit([&](auto&& tmp)
				{
					tmp.ChangeValue(val);
				}, *curr);
		}
	}
}

void Path::GetNeighbor()
{
	if (!parent)
		return;

	(!neighbors.empty() || [&]() { neighbors.clear(); return false; }());
	neighbors.resize(4, nullptr);

	size_t it = 0;
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	for (uint8_t i = 0; i < 4; ++i)
	{
		IVec2 newPos = pos + Sides[i];
		if (newPos.x < 0 || newPos.y < 0 || newPos.x >= parent->MazeSize.x || newPos.y >= parent->MazeSize.y)
		{
			continue;
		}

		neighbors[it++] = parent->GetCellByPos(newPos);
	}
}
