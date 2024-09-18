#pragma once

#include <cmath>

template <typename type>
struct Vec2
{
	type x, y;

	template <typename OtherType>
	void operator()(OtherType op) const
	{
		x = static_cast<type>(op.x);
		y = static_cast<type>(op.y);
	}

	template <typename OtherType>
	Vec2(OtherType _x, OtherType _y) : x(static_cast<type>(_x)), y(static_cast<type>(_y)) {}

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
		x = static_cast<type>(op.x); y = static_cast<type>(op.y);
	}

	template <typename operandType>
	Vec2<type> operator+(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x + static_cast<type>(op.x), y + static_cast<type>(op.y));
	}

	template <typename operandType>
	Vec2<type> operator-(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x - static_cast<type>(op.x), y - static_cast<type>(op.y));
	}

	template <typename operandType>
	void operator+=(const Vec2<operandType>& op)
	{
		x += static_cast<type>(op.x); y += static_cast<type>(op.y);
	}

	double squareLength() const
	{
		return x * x + y * y;
	}

	double length() const
	{
		return std::sqrt(squareLength());
	}

};

using FVec2 = Vec2<float>;
using IVec2 = Vec2<int>;
