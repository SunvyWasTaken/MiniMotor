// Copyright Shimmer Studios : All rights reserved.

#include "ECS/Entitys.h"
#include "World.h"

Entity::Entity()
	: m_Entity(entt::null)
	, m_World(nullptr)
{
}

Entity::Entity(const Entity& other)
	: m_Entity(other.m_Entity)
	, m_World(other.m_World)
{
}

Entity::Entity(const entt::entity& entity, World* world)
	: m_Entity(entity)
	, m_World(world)
{
}

Entity& Entity::operator=(const Entity& other)
{
	m_Entity = other.m_Entity;
	m_World = other.m_World;
	return *this;
}

Entity::~Entity()
{
}

World* Entity::GetWorld()
{
	return m_World;
}

void Entity::AddWorldOffset(const FVec2& offset)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.transform.pos += offset;
}

const FVec2& Entity::GetWorldPosition() const
{
	return GetComponent<TransformComponent>().transform.pos;
}

void Entity::SetSize(const FVec2& size)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.transform.scale = size;
}
