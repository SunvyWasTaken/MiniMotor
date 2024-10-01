
#include "Cell.h"

#include "MazeTerrain.h"

#include "Debug/Debug.h"

namespace
{
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

Wall::Wall()
	: Unit<Wall>()
{
}

void Wall::ChangeValue(const uint64_t val)
{
	if(!bCanBeOpen)
		return;

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

Path::Path()
	: Unit<Path>()
{
}

void Path::ChangeValue(const uint64_t val)
{
	if (value == val)
		return;

	value = val;
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
