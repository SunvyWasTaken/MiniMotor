// Copyright Shimmer Studios : All rights reserved.

#include "World.h"

#include "ECS/Components/TagComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Entitys.h"

World::World()
{

}

World::~World()
{
}

void World::Update()
{

}

Entity World::SpawnEntity(const std::string& name)
{
	Entity entity{ m_EntityRegistry.create(), this };
	entity.AddComponent<TransformComponent>();
	entity.AddComponent<TagComponent>(name);
	return entity;
}

void World::RemoveEntity(const entt::entity& entity)
{
	m_EntityRegistry.destroy(entity);
}

void World::DrawEntitys()
{

}


