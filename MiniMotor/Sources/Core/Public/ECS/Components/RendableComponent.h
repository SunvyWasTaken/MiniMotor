// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BaseComponent.h"
#include "Textures/Textures.h"

class RendableComponent : public BaseComponent
{
public:

	RendableComponent() = default;
	virtual ~RendableComponent() = default;

	Texture texture;
};
