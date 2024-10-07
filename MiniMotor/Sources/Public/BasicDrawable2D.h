// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

class Entity;

class MM_API BasicDrawable2D
{
public:
	BasicDrawable2D();
	virtual ~BasicDrawable2D();

	FTrans2 transform;
};
