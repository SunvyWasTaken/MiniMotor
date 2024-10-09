// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "GenericRender.h"
#include "CoreMinimal.h"
#include "Entitys.h"

#include <any>

class MM_API World
{
	using EntityLists = std::vector<std::any>;

public:
	World();
	virtual ~World();

	void Update();

	template <typename RendeType>
	void BufferFrameEntitys(GenericRender<RendeType>& targetDraw)
	{
		DrawEntitys();
		for (auto [Key, vertexArray] : m_VertexArrays)
		{
			targetDraw.BufferFrame(vertexArray);
		}
	}

	template <typename EntitySpawn, typename ...Args>
	EntitySpawn* SpawnEntity(Args... args)
	{
		EntitySpawn* entity = new EntitySpawn(std::forward<Args>(args)...);
		Texture texture = entity->texture;

		if (m_VertexArrays.empty() || m_VertexArrays.find(texture.filename) == m_VertexArrays.end())
		{
			m_VertexArrays.emplace(texture.filename, VertexArray2D(texture.filename));
			m_VertexArrays.at(texture.filename).SetTexture(texture.filename);

			m_EntityGroups.emplace(texture.filename, std::make_shared<EntityLists>());
		}
		m_EntityGroups.at(texture.filename)->emplace_back(entity);
		m_VertexArrays.at(texture.filename).Resize(m_EntityGroups.at(texture.filename).get()->size());

		UpdateLastEntity(texture);
		return entity;
	}

	void RegisterEntity(Entity* entity);

	void RemoveEntity(Entity* entity);

private:

	void DrawEntitys();

	void UpdateLastEntity(const Texture& texture);

private:

	std::map<std::string, std::shared_ptr<EntityLists>> m_EntityGroups;

	std::map<std::string, VertexArray2D> m_VertexArrays;

};
