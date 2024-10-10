// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DrawableList.h"
#include "Textures/Textures.h"
#include "World.h"

class MM_API Entity
{
public:

	Entity();

	Entity(const Entity& other);

	Entity(const entt::entity& entity, World* world);

	Entity& operator=(const Entity& other);

	virtual ~Entity();

	// Get world will always return a valid world.
	// other wise it will assert by itself.
	World* GetWorld();

	void AddWorldOffset(const FVec2& offset);

	const FVec2& GetWorldPosition() const;

	void SetSize(const FVec2& size);

	template <typename ComponentType, typename ...Args>
	ComponentType& AddComponent(Args&&... args)
	{
		//assert(world->m_EntityRegistry.has<ComponentType>(m_Entity));
		return m_World->m_EntityRegistry.emplace<ComponentType>(m_Entity, std::forward<Args>(args)...);
	}

	template <typename ComponentType>
	ComponentType& GetComponent() const
	{
		return m_World->m_EntityRegistry.get<ComponentType>(m_Entity);
	}

	template <typename ...ComponentTypes>
	bool HasComponent() const
	{
		return m_World->m_EntityRegistry.any_of<ComponentTypes...>(m_Entity);
	}

	template <typename ComponentType>
	void RemoveComponent()
	{
		m_World->m_EntityRegistry.remove<ComponentType>(m_Entity);
	}

	operator const entt::entity& () const { return m_Entity; }

	operator bool () const { return m_Entity != entt::null; }

private:

	entt::entity m_Entity;

	World* m_World;

};
