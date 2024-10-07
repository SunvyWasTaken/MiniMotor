// Copyright Shimmer Studios : All rights reserved.
#pragma once

#include "BasicDrawable2D.h"

#include "Define/CRTP.h"
#include "Quad2D.h"
#include "Textures/Textures.h"

using Quad2DLists = std::vector<FQuad2D>;

class MM_API VertexArray2D : public BasicDrawable2D
{
public:

	VertexArray2D();

	virtual ~VertexArray2D();

	virtual void SetTexture(const std::string& filename);

	void Resize(const size_t size);

	FQuad2D& operator[](const size_t index);

	Quad2DLists* operator->();

public:

	Quad2DLists quads;

	Texture texture;
};

