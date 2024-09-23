#pragma once

#include "DrawableList.h"
#include "CoreMinimal.h"

class MM_API Entity
{
public:
	Entity();
	virtual ~Entity();

	void GetDrawablesList(MVectorDrawable& drawList);

	MDrawableList drawables;

};
