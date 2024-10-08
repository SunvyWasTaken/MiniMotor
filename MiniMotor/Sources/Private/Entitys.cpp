// Copyright Shimmer Studios : All rights reserved.

#include "Entitys.h"
#include "World.h"

Entity::Entity(const FVec2& pos, const FRot3& size, const Texture& _texture, World*	world)
	: transform(pos, size, {50})
	, texture(_texture)
	, m_World(world)
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{

}
