

#pragma once

#include "BasicDrawable2D.h"

#include "Define/CRTP.h"
#include "Quad2D.h"

using Quad2DLists = std::vector<FQuad2D>;

class MM_API VertexArray2D : public BasicDrawable2D
{
public:

	VertexArray2D();

	virtual ~VertexArray2D();

	void Resize(const size_t size);

	FQuad2D& operator[](const size_t index);

	Quad2DLists* operator->();

public:

	Quad2DLists quads;

};

