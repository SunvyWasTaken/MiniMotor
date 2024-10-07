#include "Geometry/VertexArray2D.h"

#include "Textures/SFMLTextures.h"

VertexArray2D::VertexArray2D()
{
}

VertexArray2D::~VertexArray2D()
{
}

void VertexArray2D::SetTexture(const std::string& filename)
{
	SFMLTextures::GetInstance()->LoadTexture(filename);
	texture.filename = filename;

	for (FQuad2D& quad : quads)
	{
		quad.SetTexture(&texture);
	}
}

void VertexArray2D::Resize(const size_t size)
{
	quads.resize(size);
}

FQuad2D& VertexArray2D::operator[](const size_t index)
{
	return quads[index];
}

Quad2DLists* VertexArray2D::operator->()
{
	return &quads;
}
