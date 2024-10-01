
#pragma once

#include "Define/CRTP.h"

#include "CoreMinimal.h"

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
		, pos(0, 0)
		, bCanBeOpen(false)
	{}
	
	virtual ~Unit() = default;

	void SetValue(const uint64_t val)
	{
		value = val;
	}

	CRTP_CALL_OneParam(ChangeValue, const uint64_t)

	MazeTerrain* parent;

	uint64_t value;

	IVec2 pos;

	bool bCanBeOpen;
};

using Cell = std::variant<Unit<Wall>, Unit<Path>>;

class Wall : public Unit<Wall>
{
public:

	Wall();

	void ChangeValue(const uint64_t val);
};

class Path : public Unit<Path>
{
public:

	Path();

	void ChangeValue(const uint64_t val);
};

