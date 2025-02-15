#pragma once

#include "Maths.h"

namespace Sunset
{
	class TransformComponent
	{
	public:

		explicit TransformComponent(const Transform& trans)
			: transform(trans)
		{
		}

		Transform& operator()()
		{
			return transform;
		}

		Transform transform;
	};
}
