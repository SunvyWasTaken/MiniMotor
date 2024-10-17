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

	virtual ~Entity();

	virtual void BeginPlay();

	virtual void Update(float deltaTime);

	void Destroy();

	World* GetWorld();

/************************************************************************/
/* WorldPosition														*/
/************************************************************************/

	const FVec2& GetWorldPosition() const;

	void SetWorldPosition(const FVec2& pos);

	void AddWorldOffset(const FVec2& offset);

/************************************************************************/
/* Transform															*/
/************************************************************************/

	const FVec2& GetSize() const;

	void SetSize(const FVec2& size);

	template <typename ComponentType, typename ...Args>
	ComponentType& AddComponent(Args&&... args)
	{
		return m_EntityId.m_World->m_EntityRegistry.emplace<ComponentType>(m_EntityId.m_Id, std::forward<Args>(args)...);
	}

	template <typename ComponentType>
	ComponentType& GetComponent() const
	{
		return  m_EntityId.m_World->m_EntityRegistry.get<ComponentType>(m_EntityId.m_Id);
	}

	template <typename ...ComponentTypes>
	bool HasComponent() const
	{
		return  m_EntityId.m_World->m_EntityRegistry.any_of<ComponentTypes...>(m_EntityId.m_Id);
	}

	template <typename ComponentType>
	void RemoveComponent()
	{
		m_EntityId.m_World->m_EntityRegistry.remove<ComponentType>(m_EntityId.m_Id);
	}

	operator const entt::entity& () const { return m_EntityId; }

	operator bool () const { return m_EntityId; }

private:

	EntityId m_EntityId;

	friend class World;
};
