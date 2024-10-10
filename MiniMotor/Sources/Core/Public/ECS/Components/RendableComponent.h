// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BaseComponent.h"
#include "Textures/Textures.h"

class MM_API RendableComponent : public BaseComponent
{
public:

	RendableComponent() = default;

	explicit RendableComponent(const Texture& textu);

	virtual ~RendableComponent() = default;

	Texture texture;
};
