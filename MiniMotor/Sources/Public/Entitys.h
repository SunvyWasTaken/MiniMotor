// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "DrawableList.h"
#include "CoreMinimal.h"
#include "Textures/Textures.h"

class MM_API Entity
{
public:
	Entity();

	virtual ~Entity();

	virtual void Update(float deltaTime);

	FTrans2 transform;
	Texture texture;
};
