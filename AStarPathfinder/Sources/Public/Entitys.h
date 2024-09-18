#pragma once

#include "Vec2.h"

#include <vector>
#include <string>

class IEntity
{
public:
	IEntity(std::string character, IVec2 location);

	virtual ~IEntity() = default;

	virtual void SetValue(int value);

	virtual bool IsCell() const;

	std::string Character;
	IVec2 Location;
};

class Player : public IEntity
{
public:
	Player(IVec2 location);

	~Player() = default;

};

class Wall : public IEntity
{
public:
	Wall(IVec2 location);

	~Wall() = default;
	bool IsLocked = false;

};


class Cell : public IEntity
{
public:
	Cell(IVec2 location);

	~Cell() = default;

	virtual void SetValue(int value) override;

	virtual bool IsCell() const override { return true; }

	std::vector<Cell*> Neighbors;

	int CurrentValue = -1;
};


class EndPoint : public IEntity
{
public:
	EndPoint(IVec2 location);

	~EndPoint() = default;

};

