
#pragma once

#include "Geometry/Quad2D.h"

template <typename T>
inline void Quad2D<T>::FillColor(const Color& color)
{
	for (auto& vertice : vertices)
	{
		vertice.color = color;
	}
};