// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BaseComponent.h"

class MM_API TagComponent : public BaseComponent
{
public:

	explicit TagComponent(const std::string& name = std::string());
	virtual ~TagComponent() = default;

	const std::string tag;
};