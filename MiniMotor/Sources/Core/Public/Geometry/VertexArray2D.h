// Copyright Shimmer Studios : All rights reserved.
#pragma once

#include "BasicDrawable2D.h"

#include "Define/CRTP.h"
#include "Quad2D.h"
#include "Textures/Textures.h"

using Quad2DLists = std::vector<FQuad2D>;

class MM_API VertexArray2D
{
public:

	explicit VertexArray2D(const std::string& textureName = "");

	virtual ~VertexArray2D();

	virtual void SetTexture(const std::string& filename);

	void Resize(const size_t size);

	size_t Size() const;

	void AddQuad(const FTrans2& trans, const Texture& textu);

	FQuad2D& operator[](const size_t index);

	const FQuad2D& operator[](const size_t index) const;

	Quad2DLists* operator->();

public:

	Quad2DLists quads;

	Texture texture;
};

