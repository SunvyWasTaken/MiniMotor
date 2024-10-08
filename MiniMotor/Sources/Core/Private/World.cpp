#include "World.h"

#include "Entitys.h"

World::World()
{

}

World::~World()
{
}

void World::Update()
{
	//for (auto& [Key, val] : m_EntityGroups)
	//{
	//	for (auto& entity : *val)
	//	{
	//		entity->Update(0.5);
	//	}
	//}
}

void World::RemoveEntity(Entity* entity)
{
	for (auto& [Key, val] : m_EntityGroups)
	{
		for (uint64_t i = 0; i < val->size(); ++i)
		{
			if (val->at(i).get() == entity)
			{
				val->erase(val->begin() + i);
				m_VertexArrays[Key].quads.erase(m_VertexArrays[Key].quads.begin() + i);
				break;
			}
		}
	}
}

void World::DrawEntitys()
{
	// Not supposed to be huge.
	for (auto& [Key, val] : m_VertexArrays)
	{
		EntityLists& entitys = *m_EntityGroups.at(Key).get();
		for (uint64_t i = 0; i < entitys.size(); ++i)
		{
			val[i].transform.pos = entitys[i]->transform.pos * entitys[i]->transform.scale;
			val[i].transform.rot = entitys[i]->transform.rot;
			val[i].transform.scale = entitys[i]->transform.scale;
		}
	}
}

void World::UpdateLastEntity(const Texture& texture)
{
	const size_t index = m_EntityGroups[texture.filename].get()->size() - 1;
	m_VertexArrays[texture.filename][index].SetCoord(texture.coord);
}

