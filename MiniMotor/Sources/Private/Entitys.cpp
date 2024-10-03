
#include "Entitys.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{

}

void Entity::GetDrawablesList(MVectorDrawable& drawList)
{
	for (auto& [key, drawable] : drawables)
	{
		drawList.push_back(drawable);
	}
}
