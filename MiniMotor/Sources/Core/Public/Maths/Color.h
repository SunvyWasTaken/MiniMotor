// Copyright Shimmer Studios : All rights reserved.

#pragma once

template <typename T>
struct MM_EXPORT Color
{
	Color() : r(255), g(255), b(255), a(255) {}

	Color(T r, T g, T b, T a = 255) : r(r), g(g), b(b), a(a) {}

	T r, g, b, a;

	static Color<T> Red;
};

using FColor = Color<unsigned char>;

FColor FColor::Red{255, 0, 0};
