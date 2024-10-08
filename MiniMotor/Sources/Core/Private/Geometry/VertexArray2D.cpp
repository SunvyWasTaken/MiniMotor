#include "Geometry/VertexArray2D.h"

#include "Textures/SFMLTextures.h"

VertexArray2D::VertexArray2D(const std::string& textureName)
	: texture(textureName, {0})
{
}

VertexArray2D::~VertexArray2D()
{
}

void VertexArray2D::SetTexture(const std::string& filename)
{
	SFMLTextures::GetInstance()->LoadTexture(filename);
	texture.filename = filename;
}

void VertexArray2D::Resize(const size_t size)
{
	quads.resize(size);
}

size_t VertexArray2D::Size() const
{
	return quads.size();
}

FQuad2D& VertexArray2D::operator[](const size_t index)
{
	return quads[index];
}

const FQuad2D& VertexArray2D::operator[](const size_t index) const
{
	return quads[index];
}

Quad2DLists* VertexArray2D::operator->()
{
	return &quads;
}
