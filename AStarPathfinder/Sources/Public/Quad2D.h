
#pragma once

#include "BasicDrawable2D.h"
#include "Utils/Typelist.h"
#include "Vertex2D.h"

#include <array>

namespace Side
{
	struct TopLeft {};
	struct TopRight {};
	struct BottomLeft {};
	struct BottomRight {};
}

using QuadSide = Typelist<Side::TopLeft, Side::TopRight, Side::BottomRight, Side::BottomLeft>;

template <typename T>
struct Quad2D : public BasicDrawable2D
{
	using vertice_type = Vertex2D<T>;
	using Vertex2DArray = std::array<vertice_type, 4>;

public:

	Quad2D()
	{
		vertices[0].position = Vec2<T>(0, 0);
		vertices[1].position = Vec2<T>(1, 0);
		vertices[2].position = Vec2<T>(1, 1);
		vertices[3].position = Vec2<T>(0, 1);
	}

	template <typename TargetSide>
	vertice_type GetVertice() const
	{
		constexpr int index = GetTypelistIndex<TargetSide, QuadSide>::value;
		static_assert(index != -1, "Invalid side");
		return vertices[index];
	}

	template <typename TargetSide>
	vertice_type& GetVertice()
	{
		constexpr int index = GetTypelistIndex<TargetSide, QuadSide>::value;
		static_assert(index != -1, "Invalid side");
		return vertices[index];
	}

	template <typename TargetSide>
	Vec2<T> GetVerticePosition() const
	{
		return (GetVertice<TargetSide>().position * transform.scale) + transform.pos;
	}

	void FillColor(const Color& color)
	{
		for (auto& vertice : vertices)
		{
			vertice.color = color;
		}
	}

public:
	Vertex2DArray vertices;

};

using FQuad2D = Quad2D<double>;
