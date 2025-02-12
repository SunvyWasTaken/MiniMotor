#pragma once

#include "Scene.h"

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;

	template <typename T, typename ...Args>
	void AddComponent(Args&&... args)
	{
		world->entitys.emplace<T>(std::forward<Args>(args)...);
	}

private:
	
	void Init(const entt::entity& _id, Scene* _world);

private:

	entt::entity id;
	// todo : should be like a weak pointer of maybe?
	Scene* world;

	friend Scene;
};
