// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "GenericRender.h"
#include "CoreMinimal.h"
#include "Entitys.h"

class MM_API World
{
	using EntityLists = std::vector<std::unique_ptr<Entity>>;

public:
	World();
	virtual ~World();

	void Update();

	template <typename RendeType>
	void BufferFrameEntitys(GenericRender<RendeType>& targetDraw)
	{
		for (auto [Key, vertexArray] : m_VertexArrays)
		{
			targetDraw.BufferFrame(vertexArray);
		}
	}

	template <typename EntitySpawn>
	EntitySpawn* SpawnEntity(const IVec2& position, const IVec2& size, const Texture& texture = "")
	{
		if (m_VertexArrays.find(texture.filename) == m_VertexArrays.end())
		{
			m_VertexArrays.emplace(texture.filename, VertexArray2D());
			m_VertexArrays.at(texture.filename).SetTexture(texture.filename);

			m_EntityGroups.emplace(texture.filename, std::make_shared<EntityLists>());
		}
		EntitySpawn* entity = new EntitySpawn(position, size, texture, this);
		m_EntityGroups.at(texture.filename)->emplace_back(entity);
		UpdateLastEntity(texture);

		m_VertexArrays.at(texture.filename).Resize(m_EntityGroups.size());
		return entity;
	}

private:

	void DrawEntitys();

	void UpdateLastEntity(const Texture& texture);

private:

	std::map<std::string, std::shared_ptr<EntityLists>> m_EntityGroups;

	std::map<std::string, VertexArray2D> m_VertexArrays;

};
