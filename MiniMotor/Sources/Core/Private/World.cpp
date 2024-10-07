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

void World::DrawEntitys()
{
	// Not supposed to be huge.
	//for (auto [Key, val] : m_VertexArrays)
	//{
	//	//EntityLists& entitys = *m_EntityGroups.at(Key).get();
	//	//for (uint64_t i = 0; i < entitys.size(); ++i)
	//	//{
	//	//	val[i].transform.pos = entitys[i]->transform.pos;
	//	//	val[i].transform.rot = entitys[i]->transform.rot;
	//	//	val[i].transform.scale = entitys[i]->transform.scale;
	//	//}
	//}
}

void World::UpdateLastEntity(const std::string& texture)
{
	//(m_VertexArrays[texture])[m_EntityGroups[texture]->size() - 4].getVertice<Side::TopLeft>().position = Vec2<float>(0, 0);
}

