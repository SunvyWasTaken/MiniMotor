
#pragma once

#include "Define/CRTP.h"

#include "Vec2.h"

#include <array>
#include <variant>
#include <vector>

class Path;
class Wall;
class MazeTerrain;

template <typename Derived>
class Unit
{
public:

	Unit()
		: parent(nullptr)
		, value(0)
	{}
	
	virtual ~Unit() = default;

	void SetValue(const uint64_t val)
	{
		value = val;
	}

	CRTP_CALL_OneParam(ChangeValue, uint64_t)

	CRTP_CALL(GetNeighbor)

	uint64_t value;

	IVec2 pos;

	MazeTerrain* parent;
};

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class Wall : public Unit<Wall>
{
public:

	Wall();

	void ChangeValue(uint64_t val);

	void GetNeighbor();

	std::vector<Unit<Path>*> neighbors;
};

class Path : public Unit<Path>
{
public:

	Path();

	void ChangeValue(uint64_t val);

	void GetNeighbor();

	std::vector<Cell*> neighbors;
};

