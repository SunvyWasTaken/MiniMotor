
#pragma once

#include "CoreMinimal.h"
#include "ECS/Entitys.h"

class Path;
class Wall;
class MazeTerrain;

template <typename Derived>
class Unit
{
public:

	Unit(const IVec2& pos, const TextureCoord& texCoord, class World* world)
		: Entity(pos, FRot3(0), Texture("Ressources/Brick_Block.png", texCoord), world)
		, parent(nullptr)
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

	CRTP_CALL_OneParam(ChangeValue, const uint64_t)

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

	Wall(const IVec2& pos, class World* world);

	void ChangeValue(const uint64_t val);
};

class Path : public Unit<Path>
{
public:

	Path(const IVec2& pos, class World* world);

	void ChangeValue(const uint64_t val);

	std::vector<Unit<Path>*> GetNeighbours();
};

