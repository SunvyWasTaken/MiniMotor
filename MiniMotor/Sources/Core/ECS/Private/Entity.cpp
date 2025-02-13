#include "LeafEntity.h"
#include "Scene.h"

Entity::~Entity()
{
	
}

void Entity::InitImpl(const entt::entity& _id, Scene* _world)
{
	id = _id;
	world = _world;
}

