// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "DrawableList.h"
#include "CoreMinimal.h"

class MM_API Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float deltaTime);

	void GetDrawablesList(MVectorDrawable& drawList);

	MDrawableList drawables;

};
