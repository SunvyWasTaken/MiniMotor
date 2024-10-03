#include "World.h"

#include "Entitys.h"

World::World()
{
}

World::~World()
{
}

void World::Update()
{
	for (auto& entity : Entities)
	{
		entity->Update(0.5);
	}
}

