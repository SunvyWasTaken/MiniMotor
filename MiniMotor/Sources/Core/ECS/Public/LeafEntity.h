#pragma once

#include <entt/entt.hpp>

namespace Sunset
{
	class Scene;

	class MM_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		// todo : I thought template need the definition of the function to compile WTF
		template <typename T, typename ...Args>
		void AddComponent(Args&&... args);

		template <typename T>
		T& GetComponent() const;

	private:

		void InitImpl(const entt::entity& _id, Scene* _world);

		virtual void Init() {};

		virtual void Update(float deltatime) {};

	private:

		entt::entity id;
		// todo : should be like a weak pointer of maybe?
		Scene* world;

		friend Scene;
	};
}
