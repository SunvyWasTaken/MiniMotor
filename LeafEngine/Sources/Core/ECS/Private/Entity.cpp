#include "Entity.h"

void Entity::Init(const entt::entity& _id, Scene* _world)
{
	id = _id;
	world = _world;
}
