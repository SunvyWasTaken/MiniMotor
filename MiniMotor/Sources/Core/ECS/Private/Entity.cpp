#include "LeafEntity.h"
#include "Scene.h"
namespace Sunset
{
	Entity::Entity()
		: id(entt::null)
		, world(nullptr)
	{
	}

	Entity::~Entity()
	{
		std::cerr << "Explosion" << std::endl;
	}

	void Entity::InitImpl(const entt::entity& _id, Scene* _world)
	{
		id = _id;
		world = _world;
	}
}

