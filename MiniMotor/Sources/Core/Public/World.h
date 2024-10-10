// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericRender.h"
#include "ECS/Components/RendableComponent.h"
#include "ECS/Components/TransformComponent.h"

#include "entt/entt.hpp"

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

	Entity SpawnEntity(const std::string& name);

	void RemoveEntity(const entt::entity& entity);

private:

	void DrawEntitys();

private:
	
	entt::registry m_EntityRegistry;

	friend class Entity;

};
