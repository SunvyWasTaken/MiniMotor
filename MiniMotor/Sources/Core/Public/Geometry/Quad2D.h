// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "BasicDrawable2D.h"
#include "Vertex2D.h"
#include "Textures/Textures.h"

template <typename T>
struct MM_EXPORT Quad2D : public BasicDrawable2D
{
	using vertice_type = Vertex2D<T>;
	using Vertex2DArray = std::array<vertice_type, GetSizelist<QuadSide>::value>;

public:

	Quad2D(const FTrans2& trans = {FVec2{1, 1}, FRot3{0, 0, 0}, FVec2{10, 10}})
		: BasicDrawable2D(trans)
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

	void FillColor(const FColor& color)
	{
		for (auto& vertice : vertices)
		{
			vertice.color = color;
		}
	}

	void SetCoord(const TextureCoord& coord)
	{
		for (unsigned int i = 0; i < GetSizelist<QuadSide>::value; ++i)
		{
			vertices[i].texCoords = coord[i];
		}
	}

public:
	Vertex2DArray vertices;
};

using FQuad2D = Quad2D<double>;
