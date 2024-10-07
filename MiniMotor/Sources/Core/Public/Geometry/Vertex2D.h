// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

template <typename T>
struct MM_API Vertex2D
{
	Vec2<T> position;
	Vec2<T> texCoords;
	FColor color;
};
