// Copyright Shimmer Studios : All rights reserved.

#include "ECS/Entitys.h"

Entity::Entity()
	: m_EntityId()
{
}

Entity::~Entity()
{
}

void Entity::BeginPlay()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::Destroy()
{
	m_EntityId.m_World->RemoveEntity(*this);
}

World* Entity::GetWorld()
{
	return m_EntityId.m_World;
}

const FVec2& Entity::GetWorldPosition() const
{
	return GetComponent<TransformComponent>().transform.pos;
}

void Entity::SetWorldPosition(const FVec2& pos)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.transform.pos = pos;
}

void Entity::AddWorldOffset(const FVec2& offset)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.transform.pos += offset;
}

const FVec2& Entity::GetSize() const
{
	return GetComponent<TransformComponent>().transform.scale;
}

void Entity::SetSize(const FVec2& size)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.transform.scale = size;
}
