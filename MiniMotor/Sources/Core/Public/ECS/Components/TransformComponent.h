// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BaseComponent.h"

class TransformComponent : public BaseComponent
{
public:

	TransformComponent() = default;
	virtual ~TransformComponent() = default;

	FTrans2 transform;
};