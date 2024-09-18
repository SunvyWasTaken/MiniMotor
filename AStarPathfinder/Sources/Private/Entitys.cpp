
#include "Entitys.h"

IEntity::IEntity(std::string character = { 0 }, IVec2 location = { 0, 0 }) : Character(character), Location(location)
{

}

void IEntity::SetValue(int value)
{
}

bool IEntity::IsCell() const
{
	return false;
}

Player::Player(IVec2 location) : IEntity("P", location)
{}

Wall::Wall(IVec2 location) : IEntity("+", location)
{}

void Cell::SetValue(int value)
{
	if (CurrentValue == value)
	{
		return;
	}
	CurrentValue = value;
	for (auto tmp : Neighbors)
	{
		tmp->SetValue(value);
	}
}

Cell::Cell(IVec2 location) : IEntity(" ", location)
{}

EndPoint::EndPoint(IVec2 location) : IEntity("E", location)
{
}
