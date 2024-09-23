
#pragma once

#include "CoreMinimal.h"

struct MM_EXPORT Color
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;
};

template <typename T>
struct MM_API Vertex2D
{
	Vec2<T> position;
	Vec2<T> texCoords;
	Color color;
};
