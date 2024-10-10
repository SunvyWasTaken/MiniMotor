
#pragma once

#include "CoreMinimal.h"
#include "ECS/Entitys.h"
#include "MazeTerrain.h"

class Path;
class Wall;

template <typename Derived>
class Unit
{
public:

	Unit(const IVec2& pos, class MazeTerrain* world)
		: parent(world)
		, value(0)
		, bCanBeOpen(false)
		, beforePath(nullptr)
		, gCost(0)
		, hCost(0)
	{}
	
	virtual ~Unit() = default;

	void SetValue(const uint64_t val)
	{
		value = val;
	}

	std::vector<Unit<Path>*> GetNeighbours()
	{
		Derived* derived = static_cast<Derived*>(this);
		return derived->GetNeighbours();
	}

	CRTP_CALL_Variadic(Derived, ChangeValue)

	MazeTerrain* parent;

	uint64_t value;

	bool bCanBeOpen;

	// A* Pathfinding
	Unit<Path>* beforePath;

	uint64_t gCost;

	uint64_t hCost;
};

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class Wall : public Unit<Wall>
{
public:

	Wall(const IVec2& pos, class MazeTerrain* world);

	void ChangeValue(const uint64_t val, const Entity& entity);
};

class Path : public Unit<Path>
{
public:

	Path(const IVec2& pos, class MazeTerrain* world);

	void ChangeValue(const uint64_t val, const Entity& entity);

	std::vector<Unit<Path>*> GetNeighbours();
};

