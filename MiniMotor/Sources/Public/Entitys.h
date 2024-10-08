// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "DrawableList.h"
#include "CoreMinimal.h"
#include "Textures/Textures.h"

class World;

class MM_API Entity
{
public:

	Entity() = default;

	Entity(const FVec2& pos, const FRot3& size, const Texture& _texture, World* world);

	virtual ~Entity();

	virtual void Update(float deltaTime);

	World* GetWorld() { return m_World; }

	FTrans2 transform;
	Texture texture;

private:

	World* m_World;

};
