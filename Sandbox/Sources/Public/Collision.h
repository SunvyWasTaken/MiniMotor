#pragma once

#include <glm/glm.hpp>

struct Sphere
{
	glm::vec3 Location;
	float Radius;
};

struct Rect
{
	glm::vec3 Location;
	float Height, Width;
};

template <typename T1, typename T2>
void TestAndResolveCollision(T1& a, T2& b)
{
	if (TestCollision(a, b))
	{
		ResolveCollision(a, b);
	}
}

template <typename T1, typename T2>
inline bool TestCollision(const T1& a, const T2& b)
{}

template <>
inline bool TestCollision(const Sphere& a, const Sphere& b)
{
	glm::vec3 vecDirection = b.Location - a.Location;
	float Distance = vecDirection.x * vecDirection.x + vecDirection.y * vecDirection.y + vecDirection.z * vecDirection.z;
	float SommeRadius = a.Radius + b.Radius;
	SommeRadius *= SommeRadius;
	return SommeRadius <= Distance;
}

template <>
inline bool TestCollision(const Rect& a, const Sphere& b)
{
	return false;
}

template <>
inline bool TestCollision(const Sphere& a, const Rect& b)
{
	return TestCollision(b, a);
}

template <>
inline bool TestCollision(const Rect& a, const Rect& b)
{
	// Pour l'axe X
	if (fabs(a.Location.x - b.Location.x) > (a.Width + b.Width))
		return false;
	// Pour l'axe Y
	if (fabs(a.Location.y - b.Location.y) > (a.Height + b.Height))
		return false;

	return true;
}

template <typename T1, typename T2>
void ResolveCollision(T1& a, T2& b)
{}

