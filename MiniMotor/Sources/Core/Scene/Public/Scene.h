#pragma once

#include "LeafEntity.h"

#include <entt/entt.hpp>

namespace Sunset
{
	class MM_API Scene
	{
	public:
		Scene();
		virtual ~Scene();

		template <typename T, typename ...Args>
		T* SpawnEntity(Args&&... args)
		{
			static_assert(std::is_base_of_v<Entity, T>, "T must be a derived class of Entity");
			entitysList.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			auto currEntity = entitysList.end() - 1;
			(*currEntity)->InitImpl(entitys.create(), this);
			(*currEntity)->Init();
			return static_cast<T*>((*currEntity).get());
		}

		void Update(float deltatime);

		entt::registry entitys;

	private:
		std::vector<std::unique_ptr<Entity>> entitysList;
		friend class Entity;
	};
}

