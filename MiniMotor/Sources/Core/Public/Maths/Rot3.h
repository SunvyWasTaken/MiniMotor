

#pragma once

template <typename T>
struct MM_EXPORT Rot3
{
	T x, y, z;

	Rot3() : x(0), y(0), z(0) {}

	template <typename U>
	Rot3(U v) : x(static_cast<T>(v)), y(static_cast<T>(v)), z(static_cast<T>(v)) {}

	template <typename U>
	Rot3(U _x, U _y, U _z) : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}

	template <typename U>
	Rot3(const Rot3<U>& r) : x(static_cast<T>(r.x)), y(static_cast<T>(r.y)), z(static_cast<T>(r.z)) {}

	template <typename U>
	Rot3& operator=(const Rot3<U>& r)
	{
		x = static_cast<T>(r.x);
		y = static_cast<T>(r.y);
		z = static_cast<T>(r.z);
		return *this;
	}

	template <typename U>
	Rot3 operator+(const Rot3<U>& r) const
	{
		return Rot3(x + static_cast<T>(r.x), y + static_cast<T>(r.y), z + static_cast<T>(r.z));
	}

	template <typename U>
	Rot3 operator-(const Rot3<U>& r) const
	{
		return Rot3(x - static_cast<T>(r.x), y - static_cast<T>(r.y), z - static_cast<T>(r.z));
	}

	template <typename U>
	Rot3 operator*(U s) const
	{
		return Rot3(x * s, y * s, z * s);
	}

	template <typename U>
	Rot3 operator/(U s) const
	{
		return Rot3(x / s, y / s, z / s);
	}

	template <typename U>
	Rot3& operator+=(const Rot3<U>& r)
	{
		x += static_cast<T>(r.x);
		y += static_cast<T>(r.y);
		z += static_cast<T>(r.z);
		return *this;
	}

	template <typename U>
	Rot3& operator-=(const Rot3<U>& r)
	{
		x -= static_cast<T>(r.x);
		y -= static_cast<T>(r.y);
		z -= static_cast<T>(r.z);
		return *this;
	}

	template <typename U>
	Rot3& operator*=(U s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	template <typename U>
	Rot3& operator/=(U s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	bool operator==(const Rot3& r) const
	{
		return x == r.x && y == r.y && z == r.z;
	}

	bool operator!=(const Rot3& r) const
	{
		return x != r.x || y != r.y || z != r.z;
	}

	Rot3 operator-() const
	{
		return Rot3(-x, -y, -z);
	}

	T dot(const Rot3& r) const
	{
		return x * r.x + y * r.y + z * r.z;
	}
};

using FRot3 = Rot3<double>;
