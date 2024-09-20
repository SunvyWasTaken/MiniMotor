#pragma once

#include <cmath>

template <typename type>
struct Vec2
{
	type x, y;

	Vec2() : x(static_cast<type>(0)), y(static_cast<type>(0)) {}

	template <typename OtherType>
	Vec2(OtherType v) : x(static_cast<type>(v)), y(static_cast<type>(v)) {}

	template <typename OtherType>
	Vec2(OtherType _x, OtherType _y) : x(static_cast<type>(_x)), y(static_cast<type>(_y)) {}

	template <typename OtherType>
	void operator()(OtherType op) const
	{
		x = static_cast<type>(op.x);
		y = static_cast<type>(op.y);
	}

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

	bool operator==(const Vec2<type>& op) const
	{
		return x == op.x && y == op.y;
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
	Vec2<type> operator*(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x * static_cast<type>(op.x), y * static_cast<type>(op.y));
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

using FVec2 = Vec2<double>;
using IVec2 = Vec2<int>;
