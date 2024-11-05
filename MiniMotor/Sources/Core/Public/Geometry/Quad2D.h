// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "Vertex2D.h"
#include "Textures/Textures.h"

template <typename T>
struct MM_EXPORT Quad_T
{
	using vertice_type = T;
	using Vertex2DArray = std::array<vertice_type, GetSizelist<QuadSide>::value>;

public:

	Quad_T()
	{
		vertices[0].position = vertice_type{0, 0};
		vertices[1].position = vertice_type{1, 0};
		vertices[2].position = vertice_type{1, 1};
		vertices[3].position = vertice_type{0, 1};

		vertices[0].texCoords = {0, 0};
		vertices[1].texCoords = {0, 0};
		vertices[2].texCoords = {0, 0};
		vertices[3].texCoords = {0, 0};
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
	vertice_type GetVerticePosition() const
	{
		return GetVertice<TargetSide>().position;
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

using FQuad2D = Quad_T<Vertex2D>;
using FQuad3D = Quad_T<Vertex3D>;
