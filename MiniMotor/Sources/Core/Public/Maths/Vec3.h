// Copyright Shimmer Studios : All rights reserved.

#pragma once

template <typename type>
struct Vec3
{
	Vec3() : x(0), y(0), z(0) {}

	Vec3(type v) : x(v), y(v), z(v) {}

	Vec3(type _x, type _y, type _z) : x(_x), y(_y), z(_z) {}

	void operator()(const Vec3<type>& op)
	{
		x = op.x;
		y = op.y;
		z = op.z;
	}

	template <typename operandType>
	bool operator<(const Vec3<operandType>& op) const
	{
		if (x != op.x) {
			return x < op.x;
		}
		if (y != op.y) {
			return y < op.y;
		}
		return z < op.z;
	}

	template <typename operandType>
	void operator=(const Vec3<operandType>& op)
	{
		x = op.x;
		y = op.y;
		z = op.z;
	}

	bool operator==(const Vec3<type>& op) const
	{
		return x == op.x && y == op.y && z == op.z;
	}

	bool operator!=(const Vec3<type>& op) const
	{
		return x != op.x || y != op.y || z != op.z;
	}

	template <typename operandType>
	Vec3<type> operator+(const operandType& op) const
	{
		return Vec3<type>(x + op, y + op, z + op);
	}

	template <typename operandType>
	Vec3<type> operator+(const Vec3<operandType>& op) const
	{
		return Vec3<type>(x + op.x, y + op.y, z + op.z);
	}

	template <typename operandType>
	Vec3<type> operator-(const Vec3<operandType>& op) const
	{
		return Vec3<type>(x - op.x, y - op.y, z - op.z);
	}

	template <typename operandType>
	Vec3<type> operator*(const Vec3<operandType>& op) const
	{
		return Vec3<type>(x * op.x, y * op.y, z * op.z);
	}

	template <typename operandType>
	Vec3<type> operator*(const operandType op) const
	{
		return Vec3<type>(x * op, y * op, z * op);
	}

	type x, y, z;
};

using FVec3 = Vec3<double>;
