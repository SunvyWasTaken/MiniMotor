#pragma once

#include "Maths.h"

class TransformComponent
{
public:

	explicit TransformComponent(const Transform& trans)
		: transform(trans)
	{ }
	
	Transform& operator()()
	{
		return transform;
	}

	Transform transform;
};
