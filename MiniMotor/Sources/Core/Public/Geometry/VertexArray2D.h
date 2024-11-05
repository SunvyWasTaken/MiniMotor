// Copyright Shimmer Studios : All rights reserved.
#pragma once

#include "Quad2D.h"
#include "Textures/Textures.h"

namespace ArrayType
{
	struct Quad{};
	struct Line{};
}


template <typename T>
class MM_API VertexArray_T
{
using VertexType = T;
using VertexLists = std::vector<VertexType>;
using TypeArray = std::variant<ArrayType::Quad, ArrayType::Line>;

public:

	explicit VertexArray_T(const TypeArray& type)
		: m_type(type)
	{
	}

	virtual ~VertexArray_T()
	{
	}

	VertexType& operator[](const size_t index)
	{
		return vertices[index];
	}

	const VertexType& operator[](const size_t index) const
	{
		return vertices[index];
	}

	VertexLists* operator->()
	{
		return &vertices;
	}

public:

	VertexLists vertices;

private:

	TypeArray m_type;
};

using VertexArray2D = VertexArray_T<Vertex2D>;
using VertexArray3D = VertexArray_T<Vertex3D>;

