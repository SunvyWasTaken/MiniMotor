
#pragma once

#include "Vec2.h"

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a = 255;
};

template <typename T>
struct Vertex2D
{
	Vec2<T> position;
	Vec2<T> texCoords;
	Color color;
};
