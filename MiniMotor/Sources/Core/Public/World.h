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
		//for (auto [Key, vertexArray] : m_VertexArrays)
		//{
		//	targetDraw.BufferFrame(vertexArray);
		//}
	}

	template <typename EntitySpawn>
	EntitySpawn* SpawnEntity(const IVec2& position, const IVec2& size, const std::string& texture = "")
	{
		//if (m_VertexArrays.find(texture) == m_VertexArrays.end())
		//{
		//	m_VertexArrays.emplace(texture, VertexArray2D());
		//	m_VertexArrays.at(texture).SetTexture(texture);

		//	m_EntityGroups.emplace(texture, EntityLists());
		//}
		//EntitySpawn* entity = new EntitySpawn(position, size, texture);
		//m_EntityGroups.at(texture)->emplace_back(entity);

		//m_VertexArrays.at(texture).Resize(m_EntityGroups.size());
		//return entity;
	}

private:

	void DrawEntitys();

	void UpdateLastEntity(const std::string& texture);

private:

	//EntityLists m_EntityList;

	// QuadTree m_QuadTree;

	std::map<std::string, std::shared_ptr<EntityLists>> m_EntityGroups;

	std::map<std::string, VertexArray2D> m_VertexArrays;

};
