// Copyright Shimmer Studios : All rights reserved.

#include "World.h"

#include "ECS/Components/CollisionComponent.h"
#include "ECS/Entitys.h"
#include "QuadTree/QuadTree.h"

#include "MiniMotorApp.h"


EntityId::EntityId()
	: m_Id(entt::null)
	, m_World(nullptr)
{
}

EntityId::EntityId(const entt::entity& id, World* world)
	: m_Id(id)
	, m_World(world)
{
}

using QuadTree = T2DQuadTree<entt::entity, FVec2>;

World::World()
{
}

World::~World()
{
}

void funcDrawRect(QuadTree* tree)
{
	MiniMotorApp* app = MiniMotorApp::GetInstance();
	if (!tree)
	{
		return;
	}

	if (tree->m_CurrentDataIndex >= 4)
	{
		app->DrawQuad(tree->m_Position, tree->m_Size, FColor::Red);
		for (auto& child : tree->m_Children)
		{
			funcDrawRect(child.get());
		}
	}
	else
	{
		app->DrawQuad(tree->m_Position, tree->m_Size, FColor::Red);
	}
};

void World::Update()
{
	for(auto& entity : m_Entitys)
	{
		entity->Update(0.0f);
	}

	std::unique_ptr<QuadTree> m_QuadTree = std::make_unique<QuadTree>(FVec2{ 0, 0 }, FVec2{ 2000, 2000 });
	for (auto entity : m_EntityRegistry.view<CollisionComponent>())
	{
		const TransformComponent& transform = m_EntityRegistry.get<TransformComponent>(entity);
		m_QuadTree->AddData(entity, transform.transform.pos);
	}

	//funcDrawRect(m_QuadTree.get());

	for (auto entity : m_EntityRegistry.view<CollisionComponent>())
	{
		bool hasCollision = false;

		const TransformComponent& transform = m_EntityRegistry.get<TransformComponent>(entity);

		std::vector<entt::entity> result;
		result.reserve(10);
		m_QuadTree->GetData(result, transform.transform);
		for (auto& coentity : result)
		{
			if (entity == coentity)
			{
				continue;
			}
			const TransformComponent& trans = m_EntityRegistry.get<TransformComponent>(coentity);
			if (transform.transform.Collide(trans.transform))
			{
				CollisionComponent& colliComponent = m_EntityRegistry.get<CollisionComponent>(entity);
				if (colliComponent.OnCollision)
				{
					hasCollision = true;
					colliComponent.IsColliding = true;
					colliComponent.OnCollision();
				}
			}
		}
		// If there was no collision
		if (!hasCollision)
		{
			CollisionComponent& colliComponent = m_EntityRegistry.get<CollisionComponent>(entity);
			if (colliComponent.IsColliding && colliComponent.OnStopCollision)
			{
				colliComponent.IsColliding = false;
				colliComponent.OnStopCollision();
			}
		}
	}

	// Ici le quadtree est automatiquement supprimé
}

void World::RemoveEntity(const Entity& entity)
{
	m_EntityRegistry.destroy(entity);
}

void World::DrawEntitys()
{

}


