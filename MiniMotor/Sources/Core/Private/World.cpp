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

void World::Update(float deltaTime)
{
	for(auto& entity : m_Entitys)
	{
		entity->Update(deltaTime);
	}

	std::unique_ptr<QuadTree> m_QuadTree = std::make_unique<QuadTree>(FVec2{ 0, 0 }, FVec2{ 2000, 2000 });
	for (auto entity : m_EntityRegistry.view<CollisionComponent>())
	{
		const TransformComponent& transform = m_EntityRegistry.get<TransformComponent>(entity);
		m_QuadTree->AddData(entity, transform.transform.pos);
	}

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
	for (auto& entity : m_EntityRegistry.view<RendableComponent>())
	{
		
	}
}

void World::PropagateInput(const KeyCode& key, bool IsPressed)
{
	for (auto& entity : m_EntityRegistry.view<InputComponent>())
	{
		InputComponent& input = m_EntityRegistry.get<InputComponent>(entity);
		if (input.callbacks.contains(key))
		{
			auto Func = input.callbacks.at(key);
			Func(IsPressed);
		}
	}
}
