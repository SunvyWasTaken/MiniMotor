#include "Scene.h"
#include "Entity.h"

namespace Sunset
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Update(float deltatime)
	{
		for (auto& entity : entitysList)
		{
			entity->Update(deltatime);
		}
	}
}
