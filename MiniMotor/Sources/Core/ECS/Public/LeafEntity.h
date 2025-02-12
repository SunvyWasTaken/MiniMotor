#pragma once

#include <entt/entt.hpp>

class Scene;

class Entity
{
public:
	Entity() = default;
	virtual ~Entity();

	// todo : I thought template need the definition of the function to compile WTF
	template <typename T, typename ...Args>
	void AddComponent(Args&&... args);

private:

	void Init(const entt::entity& _id, Scene* _world);

private:

	entt::entity id;
	// todo : should be like a weak pointer of maybe?
	Scene* world;

	friend Scene;
};
