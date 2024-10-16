// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BaseComponent.h"

class CollisionComponent : public BaseComponent
{
public:
	
	void BindOnCollision(const std::function<void()>& func)
	{
		OnCollision = func;
	}

	void BindOnStopCollision(const std::function<void()>& func)
	{
		OnStopCollision = func;
	}

private:

	bool IsColliding = false;

	friend class World;

	std::function<void()> OnCollision;

	std::function<void()> OnStopCollision;
};
