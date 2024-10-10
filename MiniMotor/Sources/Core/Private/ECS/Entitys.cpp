// Copyright Shimmer Studios : All rights reserved.

#include "ECS/Entitys.h"
#include "World.h"

Entity::Entity()
	: m_Entity(entt::null)
	, m_World(nullptr)
{
}

Entity::Entity(const entt::entity& entity, World* world)
	: m_Entity(entity)
	, m_World(world)
{
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
