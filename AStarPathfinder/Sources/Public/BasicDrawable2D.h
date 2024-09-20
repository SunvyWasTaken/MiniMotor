

#pragma once

#include "Transform2.h"

class Entity;

class BasicDrawable2D
{
public:
	BasicDrawable2D();
	virtual ~BasicDrawable2D();

	FTrans2 transform;
};
