#pragma once

#include "LeafEntity.h"
#include "Scene.h"

#include <entt/entt.hpp>

template <typename T, typename ...Args>
void Entity::AddComponent(Args&&... args)
{
	world->entitys.emplace<T>(id, std::forward<Args>(args)...);
}
