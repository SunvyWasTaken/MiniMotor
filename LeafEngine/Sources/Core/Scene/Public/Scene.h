#pragma once

#include <entt/entt.hpp>

class Entity;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	template <typename T, typename ...Args>
	T* SpawnEntity(Args&&... args)
	{
		entitysList.emplace_back(std::forward<Args>(args)...);
		auto currEntity = entitysList.end() - 1;
		(*currEntity)->Init(entitys.create(), this);
		return (*currEntity).get();
	}

private:
	std::vector<std::unique_ptr<Entity>> entitysList;
	entt::registry entitys;
	friend class Entity;
};

