
#include "Cell.h"

#include "MazeTerrain.h"

Wall::Wall() 
	: Unit<Wall>()
	, neighbors()
{
}

void Wall::ChangeValue(uint64_t val)
{
	for (auto& curr : neighbors)
	{
		if (curr->value != val)
			return;
	}
	parent->RemoveWall(this);
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
	for (Cell* curr : neighbors)
	{
		std::visit([&](auto&& tmp)
			{
				tmp.ChangeValue(val);
			}, *curr);
	}
}
