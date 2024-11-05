// Copyright Shimmer Studios : All rights reserved.

#pragma once
#include <glm/glm.hpp>

#if DEPRECATED
template <typename type>
struct MM_EXPORT Vec2
{
	type x, y;

	Vec2() : x(static_cast<type>(0)), y(static_cast<type>(0)) {}

	template <typename OtherType>
	Vec2(OtherType v) : x(static_cast<type>(v)), y(static_cast<type>(v)) {}

	template <typename OtherType>
	Vec2(OtherType _x, OtherType _y) : x(static_cast<type>(_x)), y(static_cast<type>(_y)) {}

	template <typename OtherType>
	Vec2(const Vec2<OtherType>& op) : x(static_cast<type>(op.x)), y(static_cast<type>(op.y)) {}

	template <typename OtherType>
	void operator()(OtherType op) const
	{
		x = static_cast<type>(op.x);
		y = static_cast<type>(op.y);
	}

	template <typename operandType>
	bool operator<(const Vec2<operandType>& op) const
	{
		if (x != op.x) {
			return x < op.x;
		}
		return y < op.y;
	}

	template <typename operandType>
	Vec2<type>& operator=(const Vec2<operandType>& op)
	{
		x = static_cast<type>(op.x); y = static_cast<type>(op.y);
		return *this;
	}

	Vec2<type>& operator=(const type& op)
	{
		x = op; y = op;
		return *this;
	}

	bool operator==(const Vec2<type>& op) const
	{
		return x == op.x && y == op.y;
	}

	template <typename operandType>
	bool operator==(const Vec2<operandType>& op) const
	{
		return x == op.x && y == op.y;
	}

	bool operator!=(const Vec2<type>& op) const
	{
		return x != op.x || y != op.y;
	}

	template <typename operandType>
	Vec2<type> operator+(const operandType& op) const
	{
		return Vec2<type>(x + static_cast<type>(op), y + static_cast<type>(op));
	}

	template <typename operandType>
	Vec2<type> operator+(const Vec2<operandType>& op) const
	{
		return Vec2<type>(x + static_cast<type>(op.x), y + static_cast<type>(op.y));
	}

	template <typename operandType>
	Vec2<type> operator-(const operandType& op) const
	{
		return Vec2<type>(x - static_cast<type>(op), y - static_cast<type>(op));
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
	Vec2<type> operator*(const operandType op) const
	{
		return Vec2<type>(x * static_cast<type>(op), y * static_cast<type>(op));
	}

	template <typename operandType>
	void operator+=(const Vec2<operandType>& op)
	{
		x += static_cast<type>(op.x); y += static_cast<type>(op.y);
	}

	template <typename operantType>
	Vec2<type> operator/(const operantType& op) const
	{
		return Vec2<type>(x / static_cast<type>(op), y / static_cast<type>(op));
	}

	double squareLength() const
	{
		return x * x + y * y;
	}

	double length() const
	{
		return std::sqrt(squareLength());
	}

	double Distance(const Vec2<type>& op) const
	{
		return (*this - op).length();
	}

	double dot(const Vec2<type>& op) const
	{
		return x * op.x + y * op.y;
	}

	Vec2<type> Normalize() const
	{
		double len = length();
		return Vec2<type>(x / len, y / len);
	}

	Vec2<type> rotate(double angle) const
	{
		double s = std::sin(angle);
		double c = std::cos(angle);
		return Vec2<type>(x * c - y * s, x * s + y * c);
	}

	bool Contain(const Vec2<type>& position, const Vec2<type>& size) const
	{
		return (x >= position.x - size.x && x <= position.x + size.x) && (y >= position.y - size.x && y <= position.y + size.y);
	}

};
#endif

using FVec2 = glm::vec2;
using IVec2 = glm::ivec2;
using UVec2 = glm::uvec2;
using DVec2 = glm::dvec2;
