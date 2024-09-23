
#pragma once

template <typename T>
struct MM_EXPORT Color
{
	Color() : r(0), g(0), b(0), a(255) {}

	Color(T r, T g, T b, T a = 255) : r(r), g(g), b(b), a(a) {}

	T r, g, b, a;
};

using FColor = Color<unsigned char>;
