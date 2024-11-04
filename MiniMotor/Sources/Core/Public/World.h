// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "GenericRender.h"
#include "ECS/Components/TagComponent.h"
#include "ECS/Components/RendableComponent.h"
#include "ECS/Components/TransformComponent.h"

#include "entt/entt.hpp"

class MM_API EntityId final
{
public:

	EntityId();

	EntityId(const entt::entity& id, class World* world);

	operator const entt::entity& () const { return m_Id; }

	operator bool() const { return m_Id != entt::null; }

private:

	entt::entity m_Id;
	World* m_World;

	friend class Entity;
};

class MM_API World
{
public:
	World();
	virtual ~World();

	void Update(float deltaTime);

	template <typename EntityType, typename ...Args>
	EntityType* SpawnEntity(const std::string& name, Args... args)
	{
		static_assert(std::is_base_of<Entity, EntityType>(), "EntityType must derive from Entity");

		EntityId id{m_EntityRegistry.create(), this};
		m_EntityRegistry.emplace<TagComponent>(id, name);
		m_EntityRegistry.emplace<TransformComponent>(id);

		EntityType* entity = new EntityType(std::forward<Args>(args)...);
		entity->m_EntityId = id;
		m_Entitys.push_back(std::unique_ptr<Entity>(entity));
		entity->BeginPlay();
		return entity;
	}

	void RemoveEntity(const Entity& entity);

	void DrawEntitys();

private:

	entt::registry m_EntityRegistry;

	std::vector<std::unique_ptr<Entity>> m_Entitys;

	friend class Entity;

};
