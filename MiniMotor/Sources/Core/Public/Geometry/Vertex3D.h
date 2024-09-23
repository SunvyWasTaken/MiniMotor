
#pragma once

#include "CoreMinimal.h"

struct MM_EXPORT Vertex3D
{
	using VerticesList = std::array<FVec3, 3>;

	FVec3 position;
	FVec2 texCoords;
	FVec3 normal;
	FColor color;
};
