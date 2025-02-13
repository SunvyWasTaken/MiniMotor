#pragma once

#include "Maths.h"

class TransformComponent
{
public:

	explicit TransformComponent(const FVec3& _position)
		: Position(_position)
	{ }
	
	FVec3 operator()()
	{
		return Position;
	}

	FVec3 Position;
};
