#pragma once

#include <cmath>

template <typename type>
struct Vec2
{
	type x, y;

	template <typename OtherType>
	void operator()(OtherType op) const
	{
		x = op.x;
		y = op.y;
	}

	template <typename OtherType>
	Vec2(OtherType _x, OtherType _y) : x(static_cast<OtherType>(_x)), y(static_cast<OtherType>(_y)) {}

	template <typename OtherType>
	bool operator<(const OtherType& other) const
	{
		if (x != other.x) {
			return x < other.x;
		}
		return y < other.y;
	}

	template <typename operandType>
	void operator=(const Vec2<operandType>& op)
	{
		x = op.x; y = op.y;
	}

	template <typename operandType>
	Vec2<type> operator+(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x + op.x, y + op.y);
	}

	template <typename operandType>
	Vec2<type> operator-(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x - op.x, y - op.y);
	}

	template <typename operandType>
	void operator+=(const Vec2<operandType>& op)
	{
		x += op.x; y += op.y;
	}

	double length() const
	{
		return std::sqrt(x * x + y * y);
	}

};

using FVec2 = Vec2<float>;
using IVec2 = Vec2<int>;
