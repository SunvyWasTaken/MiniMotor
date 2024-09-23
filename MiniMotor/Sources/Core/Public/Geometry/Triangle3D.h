// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

template <typename T>
struct MM_EXPORT Triangle3D
{
	using VerticesList = std::array<FVec3, 3>;

	VerticesList vertices;
};
