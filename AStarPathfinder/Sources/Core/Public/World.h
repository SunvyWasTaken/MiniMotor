
#pragma once

#include "GenericRender.h"

#include <vector>

class Entity;

class World
{
public:
	World();
	virtual ~World();

	void Update();

	template <typename RendeType>
	void BufferFrameEntitys(GenericRender<RendeType>& targetDraw)
	{
		for (auto& entity : Entities)
		{
			targetDraw.BufferFrame(entity);
		}
	}

	std::vector<Entity*> Entities;

};
