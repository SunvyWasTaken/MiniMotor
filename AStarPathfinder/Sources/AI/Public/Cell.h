
#pragma once

#include "Define/CRTP.h"

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

	uint64_t value;

	MazeTerrain* parent;
};

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class Wall : public Unit<Wall>
{
public:

	Wall();

	void ChangeValue(uint64_t val);

	std::array<Path*, 2> neighbors;
};

class Path : public Unit<Path>
{
public:

	Path();

	void ChangeValue(uint64_t val);

	std::array<Cell*, 4> neighbors;
};

