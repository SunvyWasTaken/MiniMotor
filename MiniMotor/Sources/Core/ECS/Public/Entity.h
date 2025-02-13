#pragma once

#include "LeafEntity.h"
#include "Scene.h"

#include <entt/entt.hpp>

template <typename T, typename ...Args>
inline void Entity::AddComponent(Args&&... args)
{
	world->entitys.emplace<T>(id, std::forward<Args>(args)...);
}

template<typename T>
inline T& Entity::GetComponent() const
{
	return world->entitys.get<T>(id);
}
