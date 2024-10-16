
#include "Cell.h"

#include "MazeTerrain.h"

#include "MiniDebug/Debug.h"

namespace
{
	IVec2 Sides[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
}

Wall::Wall(const IVec2& pos, class MazeTerrain* world)
	: Unit<Wall>(pos, world)
{
}

void Wall::ChangeValue(const uint64_t val, const Entity& entity)
{
	if(!bCanBeOpen)
		return;

	for (IVec2& side : Sides)
	{
		if (Cell* curr = parent->GetCellByPos(side + entity.GetWorldPosition()))
		{
			if (Unit<Path>* path = std::get_if<Unit<Path>>(curr))
			{
				if (path->value != val)
					return;
			}
		}
	}
	parent->RemoveWall(entity);
	bCanBeOpen = false;
}

Path::Path(const IVec2& pos, class MazeTerrain* world)
	: Unit<Path>(pos, world)
{
}

void Path::ChangeValue(const uint64_t val, const Entity& entity)
{
	if (value == val)
		return;

	value = val;
	for (IVec2& side : Sides)
	{
		if (side.x <= 0 || side.y <= 0 || side.x >= parent->MazeSize.x || side.y >= parent->MazeSize.y)
		{
			continue;
		}
		IVec2 tmpPos = side + entity.GetWorldPosition();
		Entity& tmpEnt = parent->Maze[tmpPos.x * parent->MazeSize.x + tmpPos.y];
		if (Cell* curr = &tmpEnt.GetComponent<Cell>())
		{
			std::visit([&](auto&& tmp)
				{
					tmp.ChangeValue(val, tmpEnt);
				}, *curr);
		}
	}
}

std::vector<Unit<Path>*> Path::GetNeighbours()
{
	std::vector<Unit<Path>*> Neighbours;
	for (IVec2& side : Sides)
	{
		//if (Cell* curr = parent->GetCellByPos(side + entity.GetWorldPosition()))
		//{
		//	if (Unit<Path>* path = std::get_if<Unit<Path>>(curr))
		//	{
		//		Neighbours.push_back(path);
		//	}
		//}
	}
	return Neighbours;
}
