#pragma once

#include "DrawableList.h"
#include "Vec2.h"

#include <string>
#include <vector>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void GetDrawablesList(MVectorDrawable& drawList);

	MDrawableList drawables;

};
