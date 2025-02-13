#pragma once

#include "LeafEntity.h"

#include <entt/entt.hpp>

class MM_API Scene
{
public:
	Scene();
	virtual ~Scene();

	template <typename T, typename ...Args>
	T* SpawnEntity(Args&&... args)
	{
		entitysList.emplace_back(new T(std::forward<Args>(args)...));
		auto currEntity = entitysList.end() - 1;
		(*currEntity)->InitImpl(entitys.create(), this);
		(*currEntity)->Init();
		return static_cast<T*>((*currEntity).get());
	}

	entt::registry entitys;

private:
	std::vector<std::unique_ptr<Entity>> entitysList;
	friend class Entity;
};

