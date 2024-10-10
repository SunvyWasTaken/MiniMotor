
#include "Cell.h"

#include "MazeTerrain.h"

#include "MiniDebug/Debug.h"

namespace
{
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

Wall::Wall(const IVec2& pos, class World* world)
	: Unit<Wall>(pos, {IVec2{0, 0}, IVec2{438, 0}, IVec2{438, 438}, IVec2{0, 438} }, world)
{
}

void Wall::ChangeValue(const uint64_t val)
{
	if(!bCanBeOpen)
		return;

	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(side + GetWorldPosition()))
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

Path::Path(const IVec2& pos, class World* world)
	: Unit<Path>(pos, { IVec2{438, 0}, IVec2{876, 0}, IVec2{876, 438}, IVec2{438, 0} }, world)
{
}

void Path::ChangeValue(const uint64_t val)
{
	if (value == val)
		return;

	value = val;
	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(side + GetWorldPosition()))
		{
			std::visit([&](auto&& tmp)
				{
					tmp.ChangeValue(val);
				}, *curr);
		}
	}
}

std::vector<Unit<Path>*> Path::GetNeighbours()
{
	std::vector<Unit<Path>*> Neighbours;
	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(side + GetWorldPosition()))
		{
			if (Unit<Path>* path = std::get_if<Unit<Path>>(curr))
			{
				Neighbours.push_back(path);
			}
		}
	}
	return Neighbours;
}
