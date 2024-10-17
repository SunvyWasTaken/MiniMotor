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

	void Update();

	// Todo : Tmp solution for vertex array draw look for merging all texture in one
	// Buffer all entitys with RendableComponent and TransformComponent
	// Idk if it's optimise cause i wanted to use vertex array instead of simple object
	// so i had to create a vertex array for each obj.
	// or i think i could merge every texture in one so there will be only one vertex array
	template <typename RendeType>
	void BufferFrameEntitys(GenericRender<RendeType>& targetDraw)
	{
		std::map<std::string, VertexArray2D> mapVertexArray;
		for (auto& entity : m_EntityRegistry.view<RendableComponent>())
		{
			const Texture& texture = m_EntityRegistry.get<RendableComponent>(entity).texture;
			if (mapVertexArray.find(texture.filename) == mapVertexArray.end())
			{
				mapVertexArray.emplace(texture.filename, VertexArray2D(texture.filename));
			}
			TransformComponent& transComp = m_EntityRegistry.get<TransformComponent>(entity);
			mapVertexArray.at(texture.filename).AddQuad(transComp.transform, texture);
		}
		for (auto& [key, value] : mapVertexArray)
		{
			targetDraw.BufferFrame(value);
		}
	}

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

private:

	void DrawEntitys();

private:

	entt::registry m_EntityRegistry;

	std::vector<std::unique_ptr<Entity>> m_Entitys;

	friend class Entity;

};
